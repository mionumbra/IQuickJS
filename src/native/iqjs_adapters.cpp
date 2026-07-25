#include "iqjs_handles.h"

#include <atomic>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <new>

using namespace iqjs;

namespace {

void throw_runtime_type_error(Handle rt_h, const char* message)
{
    for (const auto& [handle, entry] : contexts()) {
        if (entry.runtime_owner == rt_h) {
            JS_ThrowTypeError(entry.context, "%s", message);
            return;
        }
    }
}

void runtime_finalizer(JSRuntime*, void* opaque)
{
    const Handle id = static_cast<Handle>(reinterpret_cast<std::uintptr_t>(opaque));
    gm::wire::GMFunction callback;
    Handle argument = 0;
    {
        std::lock_guard<TableMutex> lock(table_mutex());
        auto it = callback_entries().find(id);
        if (it == callback_entries().end()) return;
        callback = it->second.callback;
        argument = it->second.argument;
        callback_entries().erase(it);
    }
    if (callback) callback.call(argument);
}

void class_finalizer(JSRuntime*, JSValueConst value)
{
    gm::wire::GMFunction callback;
    {
        std::lock_guard<TableMutex> lock(table_mutex());
        auto it = class_adapters().find(JS_GetClassID(value));
        if (it == class_adapters().end()) return;
        callback = it->second.finalizer;
    }
    if (callback) callback.call();
}

ClassAdapterEntry* adapter_for(JSValueConst object)
{
    auto it = class_adapters().find(JS_GetClassID(object));
    return it == class_adapters().end() ? nullptr : &it->second;
}

JSValue call_exotic(JSContext* ctx, JSValueConst object, const char* name,
                    int argc, JSValueConst* argv)
{
    auto* adapter = adapter_for(object);
    if (!adapter || adapter->context != ctx || JS_IsUndefined(adapter->exotic_methods))
        return JS_ThrowTypeError(ctx, "class exotic adapter is not installed in this context");
    JSValue function = JS_GetPropertyStr(ctx, adapter->exotic_methods, name);
    if (JS_IsException(function)) return function;
    if (!JS_IsFunction(ctx, function)) {
        JS_FreeValue(ctx, function);
        return JS_ThrowTypeError(ctx, "class exotic method '%s' is not callable", name);
    }
    JSValue result = JS_Call(ctx, function, adapter->exotic_methods, argc, argv);
    JS_FreeValue(ctx, function);
    return result;
}

int exotic_bool(JSContext* ctx, JSValueConst object, const char* name,
                int argc, JSValueConst* argv)
{
    JSValue result = call_exotic(ctx, object, name, argc, argv);
    if (JS_IsException(result)) return -1;
    int value = JS_ToBool(ctx, result);
    JS_FreeValue(ctx, result);
    return value;
}

int exotic_get_own_property(JSContext* ctx, JSPropertyDescriptor* desc,
                            JSValueConst object, JSAtom prop)
{
    JSValue key = JS_AtomToValue(ctx, prop);
    JSValue args[] = { JS_DupValue(ctx, object), key };
    JSValue result = call_exotic(ctx, object, "getOwnProperty", 2, args);
    JS_FreeValue(ctx, args[0]);
    JS_FreeValue(ctx, args[1]);
    if (JS_IsException(result)) return -1;
    if (JS_IsUndefined(result) || JS_IsNull(result)) { JS_FreeValue(ctx, result); return 0; }
    if (!JS_IsObject(result)) { JS_FreeValue(ctx, result); JS_ThrowTypeError(ctx, "getOwnProperty must return an object or undefined"); return -1; }
    if (desc) {
        desc->flags = 0;
        desc->value = JS_GetPropertyStr(ctx, result, "value");
        desc->getter = JS_GetPropertyStr(ctx, result, "get");
        desc->setter = JS_GetPropertyStr(ctx, result, "set");
        if (JS_IsException(desc->value) || JS_IsException(desc->getter) || JS_IsException(desc->setter)) {
            JS_FreeValue(ctx, desc->value);
            JS_FreeValue(ctx, desc->getter);
            JS_FreeValue(ctx, desc->setter);
            JS_FreeValue(ctx, result);
            return -1;
        }
        if (!JS_IsUndefined(desc->value)) desc->flags |= JS_PROP_HAS_VALUE;
        if (!JS_IsUndefined(desc->getter)) desc->flags |= JS_PROP_HAS_GET;
        if (!JS_IsUndefined(desc->setter)) desc->flags |= JS_PROP_HAS_SET;
        const char* names[] = { "configurable", "enumerable", "writable" };
        const int has[] = { JS_PROP_HAS_CONFIGURABLE, JS_PROP_HAS_ENUMERABLE, JS_PROP_HAS_WRITABLE };
        const int flags[] = { JS_PROP_CONFIGURABLE, JS_PROP_ENUMERABLE, JS_PROP_WRITABLE };
        for (int i = 0; i < 3; ++i) {
            JSValue v = JS_GetPropertyStr(ctx, result, names[i]);
            if (JS_IsException(v)) {
                JS_FreeValue(ctx, desc->value);
                JS_FreeValue(ctx, desc->getter);
                JS_FreeValue(ctx, desc->setter);
                JS_FreeValue(ctx, result);
                return -1;
            }
            if (!JS_IsUndefined(v)) { desc->flags |= has[i]; if (JS_ToBool(ctx, v) > 0) desc->flags |= flags[i]; }
            JS_FreeValue(ctx, v);
        }
    }
    JS_FreeValue(ctx, result);
    return 1;
}

int exotic_get_own_property_names(JSContext* ctx, JSPropertyEnum** table,
                                  std::uint32_t* length, JSValueConst object)
{
    JSValue arg = JS_DupValue(ctx, object);
    JSValue result = call_exotic(ctx, object, "getOwnPropertyNames", 1, &arg);
    JS_FreeValue(ctx, arg);
    if (JS_IsException(result)) return -1;
    if (!JS_IsArray(result)) { JS_FreeValue(ctx, result); JS_ThrowTypeError(ctx, "getOwnPropertyNames must return an array"); return -1; }
    std::int64_t count = 0;
    if (JS_GetLength(ctx, result, &count) < 0 || count < 0 || count > UINT32_MAX) { JS_FreeValue(ctx, result); return -1; }
    auto* output = static_cast<JSPropertyEnum*>(js_malloc(ctx, sizeof(JSPropertyEnum) * static_cast<size_t>(count)));
    if (!output && count) { JS_FreeValue(ctx, result); return -1; }
    std::uint32_t done = 0;
    for (; done < static_cast<std::uint32_t>(count); ++done) {
        JSValue key = JS_GetPropertyUint32(ctx, result, done);
        output[done].atom = JS_ValueToAtom(ctx, key);
        output[done].is_enumerable = false;
        JS_FreeValue(ctx, key);
        if (output[done].atom == JS_ATOM_NULL) break;
    }
    JS_FreeValue(ctx, result);
    if (done != static_cast<std::uint32_t>(count)) {
        while (done) JS_FreeAtom(ctx, output[--done].atom);
        js_free(ctx, output);
        return -1;
    }
    *table = output;
    *length = static_cast<std::uint32_t>(count);
    return 0;
}

int exotic_delete(JSContext* ctx, JSValueConst object, JSAtom prop)
{
    JSValue args[] = { JS_DupValue(ctx, object), JS_AtomToValue(ctx, prop) };
    int result = exotic_bool(ctx, object, "deleteProperty", 2, args);
    JS_FreeValue(ctx, args[0]);
    JS_FreeValue(ctx, args[1]);
    return result;
}

int exotic_define(JSContext* ctx, JSValueConst object, JSAtom prop, JSValueConst value,
                  JSValueConst getter, JSValueConst setter, int flags)
{
    JSValue descriptor = JS_NewObject(ctx);
    if (JS_IsException(descriptor)) return -1;
    if (JS_DefinePropertyValueStr(ctx, descriptor, "value", JS_DupValue(ctx, value), JS_PROP_C_W_E) < 0 ||
        JS_DefinePropertyValueStr(ctx, descriptor, "get", JS_DupValue(ctx, getter), JS_PROP_C_W_E) < 0 ||
        JS_DefinePropertyValueStr(ctx, descriptor, "set", JS_DupValue(ctx, setter), JS_PROP_C_W_E) < 0 ||
        JS_DefinePropertyValueStr(ctx, descriptor, "flags", JS_NewInt32(ctx, flags), JS_PROP_C_W_E) < 0) {
        JS_FreeValue(ctx, descriptor);
        return -1;
    }
    JSValue args[] = { JS_DupValue(ctx, object), JS_AtomToValue(ctx, prop), descriptor };
    int result = exotic_bool(ctx, object, "defineOwnProperty", 3, args);
    JS_FreeValue(ctx, args[0]);
    JS_FreeValue(ctx, args[1]);
    JS_FreeValue(ctx, args[2]);
    return result;
}

int exotic_has(JSContext* ctx, JSValueConst object, JSAtom prop)
{
    JSValue args[] = { JS_DupValue(ctx, object), JS_AtomToValue(ctx, prop) };
    int result = exotic_bool(ctx, object, "hasProperty", 2, args);
    JS_FreeValue(ctx, args[0]);
    JS_FreeValue(ctx, args[1]);
    return result;
}

JSValue exotic_get(JSContext* ctx, JSValueConst object, JSAtom prop, JSValueConst receiver)
{
    JSValue args[] = { JS_DupValue(ctx, object), JS_AtomToValue(ctx, prop), JS_DupValue(ctx, receiver) };
    JSValue result = call_exotic(ctx, object, "getProperty", 3, args);
    JS_FreeValue(ctx, args[0]);
    JS_FreeValue(ctx, args[1]);
    JS_FreeValue(ctx, args[2]);
    return result;
}

int exotic_set(JSContext* ctx, JSValueConst object, JSAtom prop, JSValueConst value,
               JSValueConst receiver, int flags)
{
    JSValue args[] = { JS_DupValue(ctx, object), JS_AtomToValue(ctx, prop), JS_DupValue(ctx, value),
                       JS_DupValue(ctx, receiver), JS_NewInt32(ctx, flags) };
    int result = exotic_bool(ctx, object, "setProperty", 5, args);
    for (JSValue arg : args) JS_FreeValue(ctx, arg);
    return result;
}

JSValue new_gml_function(Handle ctx_h, std::string_view name, std::int32_t length,
                         std::int32_t magic, const std::vector<Handle>& data,
                         const gm::wire::GMFunction& callback, Handle* registration_id = nullptr)
{
    JSContext* ctx = ctx_of(ctx_h);
    if (!ctx || !callback || length < 0 || length > 255) {
        if (ctx) JS_ThrowTypeError(ctx, "invalid GML function adapter arguments");
        return JS_EXCEPTION;
    }
    RegEntry entry{ runtime_of_context(ctx_h), resource_context(ctx_h), ctx, std::string(name), callback, {}, magic, {} };
    for (Handle handle : data) {
        auto* value = value_entry_for_context(handle, ctx_h);
        if (!value) {
            for (Handle stored_handle : entry.data) free_value(ctx_h, stored_handle);
            JS_ThrowTypeError(ctx, "invalid GML function data handle");
            return JS_EXCEPTION;
        }
        const Handle stored_handle = store_value(ctx_h, JS_DupValue(ctx, value->value));
        if (!stored_handle) {
            for (Handle handle_to_free : entry.data) free_value(ctx_h, handle_to_free);
            JS_ThrowOutOfMemory(ctx);
            return JS_EXCEPTION;
        }
        entry.data.push_back(stored_handle);
    }
    const Handle id = alloc_handle();
    if (registration_id) *registration_id = id;
    gml_funcs().emplace(id, std::move(entry));
    JSValue id_value = JS_NewInt64(ctx, static_cast<std::int64_t>(id));
    std::string function_name(name);
    JSValue function = JS_NewCFunctionData2(ctx, gml_trampoline, function_name.c_str(), length,
                                            magic, 1, &id_value);
    if (JS_IsException(function)) {
        auto it = gml_funcs().find(id);
        if (it != gml_funcs().end()) {
            for (Handle stored_handle : it->second.data) free_value(ctx_h, stored_handle);
            gml_funcs().erase(it);
        }
    }
    return function;
}

struct ClosureRegistration { Handle id; };

JSValue closure_trampoline(JSContext* ctx, JSValueConst this_value, int argc,
                           JSValueConst* argv, int magic, void* opaque)
{
    auto* closure = static_cast<ClosureRegistration*>(opaque);
    JSValue id = JS_NewInt64(ctx, static_cast<std::int64_t>(closure->id));
    return gml_trampoline(ctx, this_value, argc, argv, magic, &id);
}

void closure_finalizer(void* opaque)
{
    std::unique_ptr<ClosureRegistration> closure(static_cast<ClosureRegistration*>(opaque));
    gm::wire::GMFunction callback;
    {
        std::lock_guard<TableMutex> lock(table_mutex());
        auto it = gml_funcs().find(closure->id);
        if (it == gml_funcs().end()) return;
        callback = it->second.finalize_callback;
        gml_funcs().erase(it);
    }
    if (callback) callback.call();
}

JSValue queued_call(JSContext* ctx, int argc, JSValueConst* argv)
{
    if (argc < 1 || !JS_IsFunction(ctx, argv[0]))
        return JS_ThrowTypeError(ctx, "enqueue job target is not callable");
    return JS_Call(ctx, argv[0], JS_UNDEFINED, argc - 1, argv + 1);
}

struct SabHeader { std::atomic_size_t references{ 1 }; };
void* sab_alloc(void*, size_t size) {
    auto* header = static_cast<SabHeader*>(std::malloc(sizeof(SabHeader) + size));
    if (!header) return nullptr;
    new (header) SabHeader();
    return header + 1;
}
void sab_free(void*, void* pointer) {
    if (!pointer) return;
    auto* header = static_cast<SabHeader*>(pointer) - 1;
    if (header->references.fetch_sub(1) == 1) { header->~SabHeader(); std::free(header); }
}
void sab_dup(void*, void* pointer) {
    if (pointer) (static_cast<SabHeader*>(pointer) - 1)->references.fetch_add(1);
}

} // namespace

std::uint64_t iqjs_add_runtime_finalizer_adapter(std::uint64_t rt_h,
    const gm::wire::GMFunction& callback, std::uint64_t argument)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* rt = rt_of(rt_h);
    if (!rt || !callback) return 0;
    Handle id = alloc_handle();
    callback_entries().emplace(id, CallbackEntry{ CallbackKind::RuntimeFinalizer, rt_h, callback, argument });
    if (JS_AddRuntimeFinalizer(rt, runtime_finalizer,
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(id))) < 0) {
        callback_entries().erase(id);
        return 0;
    }
    return id;
}

void iqjs_remove_runtime_finalizer_adapter(std::uint64_t registration)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    auto it = callback_entries().find(registration);
    if (it != callback_entries().end() && it->second.kind == CallbackKind::RuntimeFinalizer)
        callback_entries().erase(it);
}

void iqjs_mark_value_adapter(std::uint64_t rt_h, std::uint64_t value_h)
{
    auto* value = value_entry(value_h);
    if (!rt_of(rt_h) || !value || value->runtime_owner != rt_h) {
        throw_runtime_type_error(rt_h, "invalid value for mark adapter");
        return;
    }
    throw_runtime_type_error(rt_h, "JS_MarkValue requires an active native GC mark function");
}

std::int32_t iqjs_new_class_adapter(std::uint64_t rt_h, std::uint64_t class_h,
    std::string_view name, const gm::wire::GMFunction& finalizer,
    const gm::wire::GMFunction& gc_mark, const gm::wire::GMFunction& call)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* rt = rt_of(rt_h);
    auto* class_entry = class_entry_for_runtime(class_h, rt_h);
    if (!rt || !class_entry || name.empty()) return -1;
    if (gc_mark || call) {
        throw_runtime_type_error(rt_h, "GML gc_mark and class call callbacks cannot satisfy synchronous QuickJS semantics");
        return -1;
    }
    auto exotic = std::make_shared<JSClassExoticMethods>();
    *exotic = { exotic_get_own_property, exotic_get_own_property_names, exotic_delete,
                exotic_define, exotic_has, exotic_get, exotic_set };
    std::string class_name(name);
    JSClassDef definition{};
    definition.class_name = class_name.c_str();
    definition.finalizer = finalizer ? class_finalizer : nullptr;
    definition.exotic = exotic.get();
    int status = JS_NewClass(rt, class_entry->class_id, &definition);
    if (status == 0) class_adapters()[class_entry->class_id] =
        ClassAdapterEntry{ rt_h, 0, nullptr, class_entry->class_id, finalizer, JS_UNDEFINED, exotic };
    return status;
}

std::int32_t iqjs_set_class_exotic_adapter(std::uint64_t ctx_h, std::uint64_t class_h,
                                            std::uint64_t methods_h)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    auto* class_entry = class_entry_for_runtime(class_h, runtime_of_context(ctx_h));
    auto* methods = value_entry_for_context(methods_h, ctx_h);
    if (!ctx || !class_entry || !methods || !JS_IsObject(methods->value)) {
        if (ctx) JS_ThrowTypeError(ctx, "invalid class exotic methods object");
        return -1;
    }
    auto adapter = class_adapters().find(class_entry->class_id);
    if (adapter == class_adapters().end()) { JS_ThrowTypeError(ctx, "class was not created by iqjs_new_class_adapter"); return -1; }
    if (adapter->second.context && adapter->second.context != ctx) {
        JS_ThrowTypeError(ctx, "class exotic adapter is already bound to another context");
        return -1;
    }
    if (!JS_IsUndefined(adapter->second.exotic_methods)) JS_FreeValue(ctx, adapter->second.exotic_methods);
    adapter->second.context_owner = ctx_h;
    adapter->second.context = ctx;
    adapter->second.exotic_methods = JS_DupValue(ctx, methods->value);
    return 0;
}

std::uint64_t iqjs_set_interrupt_handler_adapter(std::uint64_t rt_h,
                                                  const gm::wire::GMFunction&)
{
    throw_runtime_type_error(rt_h, "interrupt handlers require a synchronous return value and cannot use GMFunction dispatch");
    return 0;
}

static Handle set_notification(Handle rt_h, const gm::wire::GMFunction& callback, CallbackKind kind)
{
    JSRuntime* rt = rt_of(rt_h);
    if (!rt || !callback) return 0;
    Handle id = alloc_handle();
    callback_entries().emplace(id, CallbackEntry{ kind, rt_h, callback, 0 });
    auto& hosts = host_callbacks()[rt];
    Handle* slot = kind == CallbackKind::RejectionTracker ? &hosts.rejection_tracker : &hosts.promise_hook;
    if (*slot) callback_entries().erase(*slot);
    *slot = id;
    if (kind == CallbackKind::RejectionTracker) JS_SetHostPromiseRejectionTracker(rt, qjs_promise_rejection_tracker, nullptr);
    else JS_SetPromiseHook(rt, qjs_promise_hook, nullptr);
    return id;
}

std::uint64_t iqjs_set_host_promise_rejection_tracker_adapter(std::uint64_t rt_h,
    const gm::wire::GMFunction& callback) { std::lock_guard<TableMutex> lock(table_mutex()); return set_notification(rt_h, callback, CallbackKind::RejectionTracker); }
std::uint64_t iqjs_set_promise_hook_adapter(std::uint64_t rt_h,
    const gm::wire::GMFunction& callback) { std::lock_guard<TableMutex> lock(table_mutex()); return set_notification(rt_h, callback, CallbackKind::PromiseHook); }

void iqjs_remove_callback_adapter(std::uint64_t id)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    auto entry = callback_entries().find(id);
    if (entry == callback_entries().end()) return;
    JSRuntime* rt = rt_of(entry->second.runtime_owner);
    if (rt) {
        auto hosts = host_callbacks().find(rt);
        if (hosts != host_callbacks().end()) {
            if (hosts->second.rejection_tracker == id) { hosts->second.rejection_tracker = 0; JS_SetHostPromiseRejectionTracker(rt, nullptr, nullptr); }
            if (hosts->second.promise_hook == id) { hosts->second.promise_hook = 0; JS_SetPromiseHook(rt, nullptr, nullptr); }
        }
    }
    callback_entries().erase(entry);
}

std::uint64_t iqjs_new_gml_function_adapter(std::uint64_t ctx_h, std::string_view name,
    std::int32_t length, std::int32_t magic, const gm::wire::GMFunction& callback)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSValue function = new_gml_function(ctx_h, name, length, magic, {}, callback);
    return JS_IsException(function) ? 0 : store_value(ctx_h, function);
}

std::uint64_t iqjs_new_gml_function_data_adapter(std::uint64_t ctx_h, std::string_view name,
    std::int32_t length, std::int32_t magic, const std::vector<std::uint64_t>& data,
    const gm::wire::GMFunction& callback)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSValue function = new_gml_function(ctx_h, name, length, magic, data, callback);
    return JS_IsException(function) ? 0 : store_value(ctx_h, function);
}

std::uint64_t iqjs_new_gml_closure_adapter(std::uint64_t ctx_h, std::string_view name,
    std::int32_t length, std::int32_t magic, const gm::wire::GMFunction& callback,
    const gm::wire::GMFunction& finalize_callback)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    if (!ctx || !callback || length < 0 || length > 255) return 0;
    Handle id = alloc_handle();
    gml_funcs().emplace(id, RegEntry{ runtime_of_context(ctx_h), resource_context(ctx_h), ctx, std::string(name), callback,
                                      finalize_callback, magic, {} });
    auto* opaque = new (std::nothrow) ClosureRegistration{ id };
    if (!opaque) { gml_funcs().erase(id); return 0; }
    std::string function_name(name);
    JSValue function = JS_NewCClosure(ctx, closure_trampoline, function_name.c_str(),
                                      closure_finalizer, length, magic, opaque);
    if (JS_IsException(function)) { delete opaque; gml_funcs().erase(id); return 0; }
    return store_value(ctx_h, function);
}

std::int32_t iqjs_register_gml_global_function(std::uint64_t ctx_h, std::string_view name,
                                                const gm::wire::GMFunction& callback)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    if (!ctx || name.empty()) return -1;
    Handle registration = 0;
    JSValue function = new_gml_function(ctx_h, name, 0, 0, {}, callback, &registration);
    if (JS_IsException(function)) return -1;
    JSValue global = JS_GetGlobalObject(ctx);
    std::string property(name);
    int status = JS_SetPropertyStr(ctx, global, property.c_str(), function);
    JS_FreeValue(ctx, global);
    if (status < 0) {
        auto it = gml_funcs().find(registration);
        if (it != gml_funcs().end()) {
            for (Handle data_handle : it->second.data) free_value(ctx_h, data_handle);
            gml_funcs().erase(it);
        }
    }
    return status;
}

void iqjs_unregister_gml_global_function(std::uint64_t ctx_h, std::string_view name)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    if (!ctx) return;
    std::string property(name);
    JSValue global = JS_GetGlobalObject(ctx);
    JSAtom atom = JS_NewAtom(ctx, property.c_str());
    if (atom != JS_ATOM_NULL) { JS_DeleteProperty(ctx, global, atom, JS_PROP_THROW); JS_FreeAtom(ctx, atom); }
    JS_FreeValue(ctx, global);
    for (auto it = gml_funcs().begin(); it != gml_funcs().end();) {
        if (it->second.context_owner == resource_context(ctx_h) && it->second.name == name) it = gml_funcs().erase(it); else ++it;
    }
}

std::int32_t iqjs_enqueue_job_adapter(std::uint64_t ctx_h, std::uint64_t function_h,
                                      const std::vector<std::uint64_t>& arguments)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    auto* function = value_entry_for_context(function_h, ctx_h);
    if (!ctx || !function || !JS_IsFunction(ctx, function->value)) {
        if (ctx) JS_ThrowTypeError(ctx, "enqueue job target is not callable");
        return -1;
    }
    std::vector<JSValue> values;
    values.push_back(JS_DupValue(ctx, function->value));
    for (Handle handle : arguments) {
        auto* entry = value_entry_for_context(handle, ctx_h);
        if (!entry) { for (JSValue value : values) JS_FreeValue(ctx, value); JS_ThrowTypeError(ctx, "invalid enqueue job argument"); return -1; }
        values.push_back(JS_DupValue(ctx, entry->value));
    }
    int status = JS_EnqueueJob(ctx, queued_call, static_cast<int>(values.size()), values.data());
    for (JSValue value : values) JS_FreeValue(ctx, value);
    return status;
}

void iqjs_unsafe_set_shared_array_buffer_policy(std::uint64_t rt_h,
                                                std::string_view policy, std::uint64_t opaque)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* rt = rt_of(rt_h);
    if (!rt) return;
    if (opaque != 0) { throw_runtime_type_error(rt_h, "shared array buffer native policies do not accept opaque handles"); return; }
    if (policy == "native") {
        JSSharedArrayBufferFunctions functions{ sab_alloc, sab_free, sab_dup, nullptr };
        JS_SetSharedArrayBufferFunctions(rt, &functions);
    } else if (policy == "disabled") {
        JSSharedArrayBufferFunctions functions{};
        JS_SetSharedArrayBufferFunctions(rt, &functions);
    } else if (policy != "default") {
        throw_runtime_type_error(rt_h, "unknown shared array buffer policy");
    }
}
