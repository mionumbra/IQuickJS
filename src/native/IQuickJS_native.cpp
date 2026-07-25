#include "native/IQuickJSInternal_native.h"
#include "iqjs_handles.h"

#include <algorithm>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

using namespace iqjs;

namespace {

template <class Enum>
int enum_int(Enum value) { return static_cast<int>(value); }

std::string cstr(std::string_view value) { return std::string(value); }

bool get_context(Handle handle, JSContext*& context) {
    context = ctx_of(handle);
    return context != nullptr;
}

bool get_runtime(Handle handle, JSRuntime*& runtime) {
    runtime = rt_of(handle);
    return runtime != nullptr;
}

Handle result(Handle context, JSValue value) { return store_value(context, value); }

std::vector<JSValue> dup_values(Handle context, const std::vector<Handle>& handles, bool& valid) {
    std::vector<JSValue> output;
    output.reserve(handles.size());
    valid = true;
    for (Handle handle : handles) {
        auto* entry = value_entry_for_context(handle, context);
        if (!entry) { valid = false; break; }
        output.push_back(JS_DupValue(ctx_of(context), entry->value));
    }
    if (!valid) {
        for (JSValue value : output) JS_FreeValue(ctx_of(context), value);
        output.clear();
    }
    return output;
}

void free_owned_buffer(JSRuntime* runtime, void*, void* pointer) { js_free_rt(runtime, pointer); }

Handle owned_buffer(Handle context_handle, gm::wire::GMBuffer data, bool shared, bool uint8_array) {
    JSContext* context = ctx_of(context_handle);
    if (!context) return 0;
    auto* copy = static_cast<std::uint8_t*>(js_malloc(context, static_cast<size_t>(data.length())));
    if (!copy && data.length() != 0) return 0;
    if (data.length()) std::memcpy(copy, data.data(), static_cast<size_t>(data.length()));
    JSValue value = uint8_array
        ? JS_NewUint8Array(context, copy, static_cast<size_t>(data.length()), free_owned_buffer, nullptr, shared)
        : JS_NewArrayBuffer(context, copy, static_cast<size_t>(data.length()), free_owned_buffer, nullptr, shared);
    if (JS_IsException(value)) js_free(context, copy);
    return result(context_handle, value);
}

template <class Function>
Handle error_value(Handle context_handle, std::string_view message, Function function) {
    JSContext* context = ctx_of(context_handle);
    if (!context) return 0;
    std::string text(message);
    return result(context_handle, function(context, "%s", text.c_str()));
}

} // namespace

void iqjs_init() {}

void iqjs_shutdown() {
    std::lock_guard<TableMutex> lock(table_mutex());
    std::vector<Handle> handles;
    for (const auto& [handle, entry] : runtimes()) { (void)entry; handles.push_back(handle); }
    for (Handle handle : handles) {
        JSRuntime* runtime = rt_of(handle);
        cleanup_runtime(handle);
        runtimes().erase(handle);
        JS_FreeRuntime(runtime);
        discard_runtime_registrations(handle);
    }
}

std::uint64_t iqjs_new_runtime() {
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* runtime = JS_NewRuntime();
    if (!runtime) return 0;
    Handle handle = alloc_handle();
    runtimes().emplace(handle, RuntimeEntry{ runtime, {} });
    return handle;
}

std::uint64_t iqjs_unsafe_new_runtime_with_allocator(std::string_view policy, std::uint64_t opaque) {
    if (policy != "default" || opaque != 0) return 0;
    return iqjs_new_runtime();
}

void iqjs_free_runtime(std::uint64_t handle) {
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* runtime = rt_of(handle);
    if (!runtime) return;
    cleanup_runtime(handle);
    runtimes().erase(handle);
    JS_FreeRuntime(runtime);
    discard_runtime_registrations(handle);
}

void iqjs_set_runtime_info(std::uint64_t handle, std::string_view info) {
    std::lock_guard<TableMutex> lock(table_mutex());
    auto* entry = runtime_entry(handle);
    if (!entry) return;
    entry->info.assign(info);
    JS_SetRuntimeInfo(entry->runtime, entry->info.c_str());
}

void iqjs_set_dump_flags(std::uint64_t handle, gm_enums::IQJSDumpFlags flags) { if (auto* rt = rt_of(handle)) JS_SetDumpFlags(rt, static_cast<std::uint64_t>(flags)); }
std::uint64_t iqjs_get_dump_flags(std::uint64_t handle) { auto* rt = rt_of(handle); return rt ? JS_GetDumpFlags(rt) : 0; }
void iqjs_update_stack_top(std::uint64_t handle) { if (auto* rt = rt_of(handle)) JS_UpdateStackTop(rt); }
void iqjs_run_gc(std::uint64_t handle) { if (auto* rt = rt_of(handle)) JS_RunGC(rt); }
bool iqjs_is_live_object(std::uint64_t rt_h, std::uint64_t value_h) { auto* rt = rt_of(rt_h); auto* value = value_entry(value_h); return rt && value && value->runtime_owner == rt_h && JS_IsLiveObject(rt, value->value); }
void iqjs_set_can_block(std::uint64_t handle, bool value) { if (auto* rt = rt_of(handle)) JS_SetCanBlock(rt, value); }
std::string iqjs_get_version() { return JS_GetVersion(); }
void iqjs_unsafe_set_runtime_opaque(std::uint64_t rt_h, std::uint64_t pointer_h) { auto* rt = rt_of(rt_h); auto* pointer = pointer_entry(pointer_h); if (rt && (!pointer || pointer->runtime_owner == rt_h)) JS_SetRuntimeOpaque(rt, pointer ? pointer->pointer : nullptr); }
std::uint64_t iqjs_unsafe_get_runtime_opaque(std::uint64_t rt_h) { auto* rt = rt_of(rt_h); if (!rt) return 0; void* p = JS_GetRuntimeOpaque(rt); for (const auto& [h, e] : pointers()) if (e.runtime_owner == rt_h && e.pointer == p) return h; return 0; }

std::uint64_t iqjs_new_context(std::uint64_t rt_h) {
    std::lock_guard<TableMutex> lock(table_mutex()); auto* rt = rt_of(rt_h); if (!rt) return 0;
    JSContext* context = JS_NewContext(rt); if (!context) return 0;
    Handle handle = alloc_handle(); contexts().emplace(handle, ContextEntry{ context, rt_h, handle }); return handle;
}

std::uint64_t iqjs_new_context_raw(std::uint64_t rt_h) {
    std::lock_guard<TableMutex> lock(table_mutex()); auto* rt = rt_of(rt_h); if (!rt) return 0;
    JSContext* context = JS_NewContextRaw(rt); if (!context) return 0;
    Handle handle = alloc_handle(); contexts().emplace(handle, ContextEntry{ context, rt_h, handle }); return handle;
}

std::uint64_t iqjs_dup_context(std::uint64_t ctx_h) {
    std::lock_guard<TableMutex> lock(table_mutex()); auto* entry = context_entry(ctx_h); if (!entry) return 0;
    JSContext* context = JS_DupContext(entry->context); if (!context) return 0;
    Handle handle = alloc_handle(); contexts().emplace(handle, ContextEntry{ context, entry->runtime_owner, entry->resource_owner }); return handle;
}

void iqjs_free_context(std::uint64_t ctx_h) { std::lock_guard<TableMutex> lock(table_mutex()); JSContext* context = ctx_of(ctx_h); if (!context) return; const Handle owner = resource_context(ctx_h); bool last = true; for (const auto& [handle, entry] : contexts()) { if (handle != ctx_h && entry.resource_owner == owner) { last = false; break; } } if (last) cleanup_context(ctx_h); contexts().erase(ctx_h); JS_FreeContext(context); if (last) { discard_context_adapters(owner); discard_context_registrations(owner); } }
std::uint64_t iqjs_get_runtime(std::uint64_t ctx_h) { return runtime_of_context(ctx_h); }
void iqjs_unsafe_set_context_opaque(std::uint64_t ctx_h, std::uint64_t pointer_h) { auto* ctx = context_entry(ctx_h); auto* p = pointer_entry(pointer_h); if (ctx && (!p || (p->runtime_owner == ctx->runtime_owner && (p->context_owner == 0 || p->context_owner == resource_context(ctx_h))))) JS_SetContextOpaque(ctx->context, p ? p->pointer : nullptr); }
std::uint64_t iqjs_unsafe_get_context_opaque(std::uint64_t ctx_h) { auto* ctx = context_entry(ctx_h); if (!ctx) return 0; void* p = JS_GetContextOpaque(ctx->context); for (const auto& [h, e] : pointers()) if (e.runtime_owner == ctx->runtime_owner && e.pointer == p) return h; return 0; }
std::uint64_t iqjs_get_function_proto(std::uint64_t ctx_h) { auto* ctx = ctx_of(ctx_h); return ctx ? result(ctx_h, JS_GetFunctionProto(ctx)) : 0; }

#define IQJS_INTRINSIC(name, api) std::int32_t name(std::uint64_t h) { auto* c = ctx_of(h); return c ? api(c) : -1; }
IQJS_INTRINSIC(iqjs_add_intrinsic_base_objects, JS_AddIntrinsicBaseObjects)
IQJS_INTRINSIC(iqjs_add_intrinsic_date, JS_AddIntrinsicDate)
IQJS_INTRINSIC(iqjs_add_intrinsic_eval, JS_AddIntrinsicEval)
void iqjs_add_intrinsic_regexp_compiler(std::uint64_t h) { if (auto* c = ctx_of(h)) JS_AddIntrinsicRegExpCompiler(c); }
IQJS_INTRINSIC(iqjs_add_intrinsic_regexp, JS_AddIntrinsicRegExp)
IQJS_INTRINSIC(iqjs_add_intrinsic_json, JS_AddIntrinsicJSON)
IQJS_INTRINSIC(iqjs_add_intrinsic_proxy, JS_AddIntrinsicProxy)
IQJS_INTRINSIC(iqjs_add_intrinsic_map_set, JS_AddIntrinsicMapSet)
IQJS_INTRINSIC(iqjs_add_intrinsic_typed_arrays, JS_AddIntrinsicTypedArrays)
IQJS_INTRINSIC(iqjs_add_intrinsic_promise, JS_AddIntrinsicPromise)
IQJS_INTRINSIC(iqjs_add_intrinsic_bigint, JS_AddIntrinsicBigInt)
IQJS_INTRINSIC(iqjs_add_intrinsic_weak_ref, JS_AddIntrinsicWeakRef)
IQJS_INTRINSIC(iqjs_add_performance, JS_AddPerformance)
IQJS_INTRINSIC(iqjs_add_intrinsic_dom_exception, JS_AddIntrinsicDOMException)
IQJS_INTRINSIC(iqjs_add_intrinsic_atob, JS_AddIntrinsicAToB)
#undef IQJS_INTRINSIC

void iqjs_set_memory_limit(std::uint64_t h, std::uint64_t n) { if (auto* rt = rt_of(h)) JS_SetMemoryLimit(rt, static_cast<size_t>(n)); }
std::uint64_t iqjs_get_gc_threshold(std::uint64_t h) { auto* rt = rt_of(h); return rt ? JS_GetGCThreshold(rt) : 0; }
void iqjs_set_gc_threshold(std::uint64_t h, std::uint64_t n) { if (auto* rt = rt_of(h)) JS_SetGCThreshold(rt, static_cast<size_t>(n)); }
void iqjs_set_max_stack_size(std::uint64_t h, std::uint64_t n) { if (auto* rt = rt_of(h)) JS_SetMaxStackSize(rt, static_cast<size_t>(n)); }

gm_structs::IQJSMemoryUsage iqjs_compute_memory_usage(std::uint64_t h) {
    gm_structs::IQJSMemoryUsage o{}; auto* rt = rt_of(h); if (!rt) return o; JSMemoryUsage s{}; JS_ComputeMemoryUsage(rt, &s);
    o.malloc_size=s.malloc_size; o.malloc_limit=s.malloc_limit; o.memory_used_size=s.memory_used_size; o.malloc_count=s.malloc_count; o.memory_used_count=s.memory_used_count; o.atom_count=s.atom_count; o.atom_size=s.atom_size; o.str_count=s.str_count; o.str_size=s.str_size; o.obj_count=s.obj_count; o.obj_size=s.obj_size; o.prop_count=s.prop_count; o.prop_size=s.prop_size; o.shape_count=s.shape_count; o.shape_size=s.shape_size; o.js_func_count=s.js_func_count; o.js_func_size=s.js_func_size; o.js_func_code_size=s.js_func_code_size; o.js_func_pc2line_count=s.js_func_pc2line_count; o.js_func_pc2line_size=s.js_func_pc2line_size; o.c_func_count=s.c_func_count; o.array_count=s.array_count; o.fast_array_count=s.fast_array_count; o.fast_array_elements=s.fast_array_elements; o.binary_object_count=s.binary_object_count; o.binary_object_size=s.binary_object_size; return o;
}

std::string iqjs_dump_memory_usage(std::uint64_t h) { auto u = iqjs_compute_memory_usage(h); return "memory_used_size=" + std::to_string(u.memory_used_size) + ", malloc_size=" + std::to_string(u.malloc_size) + ", object_count=" + std::to_string(u.obj_count); }

#define IQJS_RT_ALLOC(name, api) std::uint64_t name(std::uint64_t h, std::uint64_t n) { auto* rt=rt_of(h); return rt ? store_pointer(h,0,api(rt,static_cast<size_t>(n)),PointerAllocator::Runtime) : 0; }
IQJS_RT_ALLOC(iqjs_unsafe_malloc_rt, js_malloc_rt)
IQJS_RT_ALLOC(iqjs_unsafe_mallocz_rt, js_mallocz_rt)
#undef IQJS_RT_ALLOC
std::uint64_t iqjs_unsafe_calloc_rt(std::uint64_t h,std::uint64_t n,std::uint64_t s){auto*rt=rt_of(h);return rt?store_pointer(h,0,js_calloc_rt(rt,static_cast<size_t>(n),static_cast<size_t>(s)),PointerAllocator::Runtime):0;}
std::uint64_t iqjs_unsafe_realloc_rt(std::uint64_t h,std::uint64_t p,std::uint64_t n){auto*rt=rt_of(h);PointerEntry old;if(!rt||!take_pointer(p,h,0,old)||old.allocator!=PointerAllocator::Runtime)return 0;void*q=js_realloc_rt(rt,old.pointer,static_cast<size_t>(n));if(!q&&n){pointers().emplace(p,old);return 0;}return store_pointer(h,0,q,PointerAllocator::Runtime);}
void iqjs_unsafe_free_rt(std::uint64_t h,std::uint64_t p){auto*rt=rt_of(h);PointerEntry old;if(rt&&take_pointer(p,h,0,old)&&old.allocator==PointerAllocator::Runtime)js_free_rt(rt,old.pointer);}
std::uint64_t iqjs_unsafe_malloc_usable_size_rt(std::uint64_t h,std::uint64_t p){auto*e=pointer_entry(p);auto*rt=rt_of(h);return e&&rt&&e->runtime_owner==h?js_malloc_usable_size_rt(rt,e->pointer):0;}

#define IQJS_CTX_ALLOC(name, api) std::uint64_t name(std::uint64_t h, std::uint64_t n) { auto*c=ctx_of(h);return c?store_pointer(runtime_of_context(h),h,api(c,static_cast<size_t>(n)),PointerAllocator::Context):0; }
IQJS_CTX_ALLOC(iqjs_unsafe_malloc,js_malloc)
IQJS_CTX_ALLOC(iqjs_unsafe_mallocz,js_mallocz)
#undef IQJS_CTX_ALLOC
std::uint64_t iqjs_unsafe_calloc(std::uint64_t h,std::uint64_t n,std::uint64_t s){auto*c=ctx_of(h);return c?store_pointer(runtime_of_context(h),h,js_calloc(c,static_cast<size_t>(n),static_cast<size_t>(s)),PointerAllocator::Context):0;}
std::uint64_t iqjs_unsafe_realloc(std::uint64_t h,std::uint64_t p,std::uint64_t n){auto*c=ctx_of(h);PointerEntry old;if(!c||!take_pointer(p,runtime_of_context(h),h,old)||old.allocator!=PointerAllocator::Context)return 0;void*q=js_realloc(c,old.pointer,static_cast<size_t>(n));if(!q&&n){pointers().emplace(p,old);return 0;}return store_pointer(runtime_of_context(h),h,q,PointerAllocator::Context);}
gm_structs::IQJSReallocResult iqjs_unsafe_realloc2(std::uint64_t h,std::uint64_t p,std::uint64_t n){gm_structs::IQJSReallocResult o{};auto*c=ctx_of(h);PointerEntry old;if(!c||!take_pointer(p,runtime_of_context(h),h,old)||old.allocator!=PointerAllocator::Context)return o;size_t slack=0;void*q=js_realloc2(c,old.pointer,static_cast<size_t>(n),&slack);if(!q&&n){pointers().emplace(p,old);return o;}o.pointer=store_pointer(runtime_of_context(h),h,q,PointerAllocator::Context);o.slack=slack;return o;}
void iqjs_unsafe_free(std::uint64_t h,std::uint64_t p){auto*c=ctx_of(h);PointerEntry old;if(c&&take_pointer(p,runtime_of_context(h),h,old)&&old.allocator==PointerAllocator::Context)js_free(c,old.pointer);}
std::uint64_t iqjs_unsafe_malloc_usable_size(std::uint64_t h,std::uint64_t p){auto*e=pointer_entry(p);auto*c=ctx_of(h);return e&&c&&e->context_owner==h?js_malloc_usable_size(c,e->pointer):0;}
std::uint64_t iqjs_unsafe_strdup(std::uint64_t h,std::string_view s){auto*c=ctx_of(h);if(!c)return 0;auto text=cstr(s);return store_pointer(runtime_of_context(h),h,js_strdup(c,text.c_str()),PointerAllocator::Context);}
std::uint64_t iqjs_unsafe_strndup(std::uint64_t h,std::string_view s,std::uint64_t n){auto*c=ctx_of(h);if(!c)return 0;size_t len=std::min(static_cast<size_t>(n),s.size());return store_pointer(runtime_of_context(h),h,js_strndup(c,s.data(),len),PointerAllocator::Context);}

std::uint64_t iqjs_atom_null(){return 0;}
std::uint64_t iqjs_new_atom(std::uint64_t h,std::string_view s){auto*c=ctx_of(h);if(!c)return 0;auto text=cstr(s);return store_atom(h,JS_NewAtom(c,text.c_str()));}
std::uint64_t iqjs_new_atom_len(std::uint64_t h,std::string_view s,std::uint64_t n){auto*c=ctx_of(h);return c?store_atom(h,JS_NewAtomLen(c,s.data(),std::min(static_cast<size_t>(n),s.size()))):0;}
std::uint64_t iqjs_new_atom_uint32(std::uint64_t h,std::uint32_t n){auto*c=ctx_of(h);return c?store_atom(h,JS_NewAtomUInt32(c,n)):0;}
std::uint64_t iqjs_dup_atom(std::uint64_t h,std::uint64_t a){auto*c=ctx_of(h);auto*e=atom_entry_for_context(a,h);return c&&e?store_atom(h,JS_DupAtom(c,e->atom)):0;}
std::uint64_t iqjs_dup_atom_rt(std::uint64_t h,std::uint64_t a){auto*rt=rt_of(h);auto it=atoms().find(a);if(!rt||it==atoms().end()||it->second.runtime_owner!=h)return 0;JSAtom atom=JS_DupAtomRT(rt,it->second.atom);Handle out=alloc_handle();atoms().emplace(out,AtomEntry{atom,h,it->second.context_owner});return out;}
void iqjs_free_atom(std::uint64_t h,std::uint64_t a){auto*c=ctx_of(h);auto it=atoms().find(a);if(c&&it!=atoms().end()&&it->second.runtime_owner==runtime_of_context(h)){JS_FreeAtom(c,it->second.atom);atoms().erase(it);}}
void iqjs_free_atom_rt(std::uint64_t h,std::uint64_t a){auto*rt=rt_of(h);auto it=atoms().find(a);if(rt&&it!=atoms().end()&&it->second.runtime_owner==h){JS_FreeAtomRT(rt,it->second.atom);atoms().erase(it);}}
std::uint64_t iqjs_atom_to_value(std::uint64_t h,std::uint64_t a){auto*c=ctx_of(h);auto*e=atom_entry_for_context(a,h);return c&&e?result(h,JS_AtomToValue(c,e->atom)):0;}
std::uint64_t iqjs_atom_to_string(std::uint64_t h,std::uint64_t a){auto*c=ctx_of(h);auto*e=atom_entry_for_context(a,h);return c&&e?result(h,JS_AtomToString(c,e->atom)):0;}
std::string iqjs_atom_to_cstring(std::uint64_t h,std::uint64_t a){auto*c=ctx_of(h);auto*e=atom_entry_for_context(a,h);if(!c||!e)return{};const char*p=JS_AtomToCString(c,e->atom);std::string o=p?p:"";if(p)JS_FreeCString(c,p);return o;}
std::uint64_t iqjs_value_to_atom(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?store_atom(h,JS_ValueToAtom(c,e->value)):0;}

std::uint64_t iqjs_new_class_id(std::uint64_t h){auto*rt=rt_of(h);if(!rt)return 0;JSClassID id=0;JS_NewClassID(rt,&id);Handle out=alloc_handle();class_ids().emplace(out,ClassIdEntry{id,h});return out;}
std::uint64_t iqjs_get_class_id(std::uint64_t v){auto*e=value_entry(v);if(!e)return 0;JSClassID id=JS_GetClassID(e->value);if(id==JS_INVALID_CLASS_ID)return 0;Handle out=alloc_handle();class_ids().emplace(out,ClassIdEntry{id,e->runtime_owner});return out;}
bool iqjs_is_registered_class(std::uint64_t h,std::uint64_t id){auto*rt=rt_of(h);auto*e=class_entry_for_runtime(id,h);return rt&&e&&JS_IsRegisteredClass(rt,e->class_id);}
std::uint64_t iqjs_get_class_name(std::uint64_t h,std::uint64_t id){auto*rt=rt_of(h);auto*e=class_entry_for_runtime(id,h);if(!rt||!e)return 0;JSAtom atom=JS_GetClassName(rt,e->class_id);if(atom==JS_ATOM_NULL)return 0;for(const auto&[ctx_h,c]:contexts())if(c.runtime_owner==h)return store_atom(ctx_h,atom);JS_FreeAtomRT(rt,atom);return 0;}
void iqjs_set_class_proto(std::uint64_t h,std::uint64_t id,std::uint64_t v){auto*c=ctx_of(h);auto*ce=class_entry_for_runtime(id,runtime_of_context(h));auto*ve=value_entry_for_context(v,h);if(c&&ce&&ve)JS_SetClassProto(c,ce->class_id,JS_DupValue(c,ve->value));}
std::uint64_t iqjs_get_class_proto(std::uint64_t h,std::uint64_t id){auto*c=ctx_of(h);auto*e=class_entry_for_runtime(id,runtime_of_context(h));return c&&e?result(h,JS_GetClassProto(c,e->class_id)):0;}

#define IQJS_CONST(name,value) std::uint64_t name(std::uint64_t h){return ctx_of(h)?result(h,value):0;}
IQJS_CONST(iqjs_null,JS_NULL) IQJS_CONST(iqjs_undefined,JS_UNDEFINED) IQJS_CONST(iqjs_true,JS_TRUE) IQJS_CONST(iqjs_false,JS_FALSE) IQJS_CONST(iqjs_exception,JS_EXCEPTION) IQJS_CONST(iqjs_uninitialized,JS_UNINITIALIZED)
#undef IQJS_CONST
#define IQJS_NEW(name,type,api) std::uint64_t name(std::uint64_t h,type v){auto*c=ctx_of(h);return c?result(h,api(c,v)):0;}
IQJS_NEW(iqjs_new_bool,bool,JS_NewBool) IQJS_NEW(iqjs_new_int32,std::int32_t,JS_NewInt32) IQJS_NEW(iqjs_new_int64,std::int64_t,JS_NewInt64) IQJS_NEW(iqjs_new_uint32,std::uint32_t,JS_NewUint32) IQJS_NEW(iqjs_new_uint64,std::uint64_t,JS_NewUint64) IQJS_NEW(iqjs_new_float64,float,JS_NewFloat64) IQJS_NEW(iqjs_new_number,float,JS_NewNumber) IQJS_NEW(iqjs_new_bigint64,std::int64_t,JS_NewBigInt64) IQJS_NEW(iqjs_new_biguint64,std::uint64_t,JS_NewBigUint64) IQJS_NEW(iqjs_new_catch_offset,std::int32_t,JS_NewCatchOffset)
#undef IQJS_NEW
std::uint64_t iqjs_new_string(std::uint64_t h,std::string_view s){auto*c=ctx_of(h);return c?result(h,JS_NewStringLen(c,s.data(),s.size())):0;}
std::uint64_t iqjs_new_string_len(std::uint64_t h,std::string_view s,std::uint64_t n){auto*c=ctx_of(h);return c?result(h,JS_NewStringLen(c,s.data(),std::min(static_cast<size_t>(n),s.size()))):0;}
std::uint64_t iqjs_new_string_utf16(std::uint64_t h,const std::vector<std::uint16_t>& s){auto*c=ctx_of(h);return c?result(h,JS_NewStringUTF16(c,s.data(),s.size())):0;}
std::uint64_t iqjs_new_atom_string(std::uint64_t h,std::string_view s){auto*c=ctx_of(h);if(!c)return 0;auto text=cstr(s);return result(h,JS_NewAtomString(c,text.c_str()));}
std::uint64_t iqjs_new_symbol(std::uint64_t h,std::string_view s,bool global){auto*c=ctx_of(h);if(!c)return 0;auto text=cstr(s);return result(h,JS_NewSymbol(c,text.c_str(),global));}
void iqjs_free_value(std::uint64_t h,std::uint64_t v){if(ctx_of(h))free_value(v,h);}
void iqjs_free_value_rt(std::uint64_t h,std::uint64_t v){auto*rt=rt_of(h);auto it=values().find(v);if(rt&&it!=values().end()&&it->second.runtime_owner==h){JSValue value=it->second.value;values().erase(it);JS_FreeValueRT(rt,value);}}
std::uint64_t iqjs_dup_value(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?result(h,JS_DupValue(c,e->value)):0;}
std::uint64_t iqjs_dup_value_rt(std::uint64_t h,std::uint64_t v){auto*rt=rt_of(h);auto*e=value_entry(v);if(!rt||!e||e->runtime_owner!=h)return 0;return store_value(e->context_owner,JS_DupValueRT(rt,e->value));}
std::int32_t iqjs_get_value_tag(std::uint64_t h){auto*e=value_entry(h);return e?JS_VALUE_GET_TAG(e->value):JS_TAG_EXCEPTION;}
#define IQJS_PRED(name,api) bool name(std::uint64_t h){auto*e=value_entry(h);return e&&api(e->value);}
IQJS_PRED(iqjs_is_nan,JS_VALUE_IS_NAN) IQJS_PRED(iqjs_is_number,JS_IsNumber) IQJS_PRED(iqjs_is_bigint,JS_IsBigInt) IQJS_PRED(iqjs_is_bool,JS_IsBool) IQJS_PRED(iqjs_is_null,JS_IsNull) IQJS_PRED(iqjs_is_undefined,JS_IsUndefined) IQJS_PRED(iqjs_is_exception,JS_IsException) IQJS_PRED(iqjs_is_uninitialized,JS_IsUninitialized) IQJS_PRED(iqjs_is_string,JS_IsString) IQJS_PRED(iqjs_is_symbol,JS_IsSymbol) IQJS_PRED(iqjs_is_object,JS_IsObject) IQJS_PRED(iqjs_is_module,JS_IsModule) IQJS_PRED(iqjs_is_error,JS_IsError) IQJS_PRED(iqjs_is_uncatchable_error,JS_IsUncatchableError) IQJS_PRED(iqjs_is_array_buffer,JS_IsArrayBuffer) IQJS_PRED(iqjs_is_promise,JS_IsPromise)
#undef IQJS_PRED
void iqjs_set_uncatchable_error(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(c&&e)JS_SetUncatchableError(c,e->value);}
void iqjs_clear_uncatchable_error(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(c&&e)JS_ClearUncatchableError(c,e->value);}
void iqjs_reset_uncatchable_error(std::uint64_t h){if(auto*c=ctx_of(h))JS_ResetUncatchableError(c);}
std::uint64_t iqjs_throw(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);JSValue value;if(!c||!take_value(v,h,value))return 0;return result(h,JS_Throw(c,value));}
std::uint64_t iqjs_get_exception(std::uint64_t h){auto*c=ctx_of(h);return c?result(h,JS_GetException(c)):0;}
bool iqjs_has_exception(std::uint64_t h){auto*c=ctx_of(h);return c&&JS_HasException(c);}
std::uint64_t iqjs_new_error(std::uint64_t h){auto*c=ctx_of(h);return c?result(h,JS_NewError(c)):0;}
#define IQJS_ERROR(name,api) std::uint64_t name(std::uint64_t h,std::string_view m){return error_value(h,m,api);}
IQJS_ERROR(iqjs_new_internal_error,JS_NewInternalError) IQJS_ERROR(iqjs_new_plain_error,JS_NewPlainError) IQJS_ERROR(iqjs_new_range_error,JS_NewRangeError) IQJS_ERROR(iqjs_new_reference_error,JS_NewReferenceError) IQJS_ERROR(iqjs_new_syntax_error,JS_NewSyntaxError) IQJS_ERROR(iqjs_new_type_error,JS_NewTypeError) IQJS_ERROR(iqjs_throw_internal_error,JS_ThrowInternalError) IQJS_ERROR(iqjs_throw_plain_error,JS_ThrowPlainError) IQJS_ERROR(iqjs_throw_range_error,JS_ThrowRangeError) IQJS_ERROR(iqjs_throw_reference_error,JS_ThrowReferenceError) IQJS_ERROR(iqjs_throw_syntax_error,JS_ThrowSyntaxError) IQJS_ERROR(iqjs_throw_type_error,JS_ThrowTypeError)
#undef IQJS_ERROR
std::uint64_t iqjs_throw_dom_exception(std::uint64_t h,std::string_view n,std::string_view m){auto*c=ctx_of(h);if(!c)return 0;auto name=cstr(n),message=cstr(m);return result(h,JS_ThrowDOMException(c,name.c_str(),"%s",message.c_str()));}
std::uint64_t iqjs_throw_out_of_memory(std::uint64_t h){auto*c=ctx_of(h);return c?result(h,JS_ThrowOutOfMemory(c)):0;}
#define IQJS_COMPARE(name,api,type) type name(std::uint64_t h,std::uint64_t a,std::uint64_t b){auto*c=ctx_of(h);auto*x=value_entry_for_context(a,h);auto*y=value_entry_for_context(b,h);return c&&x&&y?api(c,x->value,y->value):false;}
IQJS_COMPARE(iqjs_is_equal,JS_IsEqual,std::int32_t) IQJS_COMPARE(iqjs_is_strict_equal,JS_IsStrictEqual,bool) IQJS_COMPARE(iqjs_is_same_value,JS_IsSameValue,bool) IQJS_COMPARE(iqjs_is_same_value_zero,JS_IsSameValueZero,bool)
#undef IQJS_COMPARE
std::int32_t iqjs_to_bool(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?JS_ToBool(c,e->value):-1;}
std::uint64_t iqjs_to_boolean(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?result(h,JS_ToBoolean(c,e->value)):0;}
std::uint64_t iqjs_to_number(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?result(h,JS_ToNumber(c,e->value)):0;}
#define IQJS_CONVERT(name,Struct,Type,api) Struct name(std::uint64_t h,std::uint64_t v){Struct o{-1,0};auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(c&&e)o.status=api(c,reinterpret_cast<Type*>(&o.value),e->value);return o;}
IQJS_CONVERT(iqjs_to_int32,gm_structs::IQJSInt32Result,std::int32_t,JS_ToInt32) IQJS_CONVERT(iqjs_to_uint32,gm_structs::IQJSUInt32Result,std::uint32_t,JS_ToUint32) IQJS_CONVERT(iqjs_to_int64,gm_structs::IQJSInt64Result,std::int64_t,JS_ToInt64) IQJS_CONVERT(iqjs_to_index,gm_structs::IQJSUInt64Result,std::uint64_t,JS_ToIndex) IQJS_CONVERT(iqjs_to_bigint64,gm_structs::IQJSInt64Result,std::int64_t,JS_ToBigInt64) IQJS_CONVERT(iqjs_to_biguint64,gm_structs::IQJSUInt64Result,std::uint64_t,JS_ToBigUint64) IQJS_CONVERT(iqjs_to_int64_ext,gm_structs::IQJSInt64Result,std::int64_t,JS_ToInt64Ext)
#undef IQJS_CONVERT
gm_structs::IQJSFloatResult iqjs_to_float64(std::uint64_t h,std::uint64_t v){gm_structs::IQJSFloatResult o{-1,0};auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(c&&e){double d=0;o.status=JS_ToFloat64(c,&d,e->value);o.value=static_cast<float>(d);}return o;}
std::uint64_t iqjs_to_string(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?result(h,JS_ToString(c,e->value)):0;}
std::uint64_t iqjs_to_property_key(std::uint64_t h,std::uint64_t v){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);return c&&e?result(h,JS_ToPropertyKey(c,e->value)):0;}
std::string iqjs_to_cstring(std::uint64_t h,std::uint64_t v,bool cesu8){auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(!c||!e)return{};size_t n=0;const char*p=JS_ToCStringLen2(c,&n,e->value,cesu8);std::string o=p?std::string(p,n):std::string{};if(p)JS_FreeCString(c,p);return o;}
std::vector<std::uint16_t> iqjs_to_utf16(std::uint64_t h,std::uint64_t v){std::vector<std::uint16_t>o;auto*c=ctx_of(h);auto*e=value_entry_for_context(v,h);if(!c||!e)return o;size_t n=0;const uint16_t*p=JS_ToCStringLenUTF16(c,&n,e->value);if(p)o.assign(p,p+n);if(p)JS_FreeCStringUTF16(c,p);return o;}
