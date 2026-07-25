#pragma once

#ifdef _MSC_VER
#pragma warning(disable : 4576)
#endif

#include "native/IQuickJSInternal_native.h"
#include "quickjs.h"

#include <cstdint>
#include <mutex>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace iqjs {

using Handle = std::uint64_t;
using TableMutex = std::recursive_mutex;

enum class PointerAllocator {
    Runtime,
    Context,
    Borrowed,
};

struct RuntimeEntry {
    JSRuntime* runtime{};
    std::string info;
};

struct ContextEntry {
    JSContext* context{};
    Handle runtime_owner{};
    Handle resource_owner{};
};

struct ValueEntry {
    JSValue value{ JS_UNDEFINED };
    Handle runtime_owner{};
    Handle context_owner{};
};

struct AtomEntry {
    JSAtom atom{ JS_ATOM_NULL };
    Handle runtime_owner{};
    Handle context_owner{};
};

struct ModuleEntry {
    JSModuleDef* module{};
    Handle runtime_owner{};
    Handle context_owner{};
};

struct ModuleRegistryEntry {
    Handle runtime_owner{};
    std::unordered_map<std::string, std::string> sources;
    std::unordered_set<std::string> supported_attributes;
};

struct ClassIdEntry {
    JSClassID class_id{ JS_INVALID_CLASS_ID };
    Handle runtime_owner{};
};

struct PointerEntry {
    void* pointer{};
    Handle runtime_owner{};
    Handle context_owner{};
    PointerAllocator allocator{ PointerAllocator::Runtime };
};

struct RegEntry {
    Handle runtime_owner{};
    Handle context_owner{};
    JSContext* ctx{};
    std::string name;
    gm::wire::GMFunction callback;
    gm::wire::GMFunction finalize_callback;
    std::int32_t magic{};
    std::vector<Handle> data;
};

enum class CallbackKind {
    RuntimeFinalizer,
    Interrupt,
    RejectionTracker,
    PromiseHook,
};

struct CallbackEntry {
    CallbackKind kind{ CallbackKind::RuntimeFinalizer };
    Handle runtime_owner{};
    gm::wire::GMFunction callback;
    Handle argument{};
};

struct HostCallbacks {
    Handle interrupt{};
    Handle rejection_tracker{};
    Handle promise_hook{};
};

struct ClassAdapterEntry {
    Handle runtime_owner{};
    Handle context_owner{};
    JSContext* context{};
    JSClassID class_id{ JS_INVALID_CLASS_ID };
    gm::wire::GMFunction finalizer;
    JSValue exotic_methods{ JS_UNDEFINED };
    std::shared_ptr<JSClassExoticMethods> exotic;
};

inline TableMutex& table_mutex() { static TableMutex value; return value; }
inline Handle next_handle() { static Handle value = 0; return ++value; }
inline std::unordered_map<Handle, RuntimeEntry>& runtimes() { static std::unordered_map<Handle, RuntimeEntry> value; return value; }
inline std::unordered_map<Handle, ContextEntry>& contexts() { static std::unordered_map<Handle, ContextEntry> value; return value; }
inline std::unordered_map<Handle, ValueEntry>& values() { static std::unordered_map<Handle, ValueEntry> value; return value; }
inline std::unordered_map<Handle, AtomEntry>& atoms() { static std::unordered_map<Handle, AtomEntry> value; return value; }
inline std::unordered_map<Handle, ModuleEntry>& modules() { static std::unordered_map<Handle, ModuleEntry> value; return value; }
inline std::unordered_map<Handle, ModuleRegistryEntry>& module_registries() { static std::unordered_map<Handle, ModuleRegistryEntry> value; return value; }
inline std::unordered_map<Handle, Handle>& active_module_registries() { static std::unordered_map<Handle, Handle> value; return value; }
inline std::unordered_map<Handle, ClassIdEntry>& class_ids() { static std::unordered_map<Handle, ClassIdEntry> value; return value; }
inline std::unordered_map<Handle, PointerEntry>& pointers() { static std::unordered_map<Handle, PointerEntry> value; return value; }
inline std::unordered_map<Handle, RegEntry>& gml_funcs() { static std::unordered_map<Handle, RegEntry> value; return value; }
inline std::unordered_map<Handle, CallbackEntry>& callback_entries() { static std::unordered_map<Handle, CallbackEntry> value; return value; }
inline std::unordered_map<JSRuntime*, HostCallbacks>& host_callbacks() { static std::unordered_map<JSRuntime*, HostCallbacks> value; return value; }
inline std::unordered_map<JSClassID, ClassAdapterEntry>& class_adapters() { static std::unordered_map<JSClassID, ClassAdapterEntry> value; return value; }

inline Handle alloc_handle() { return next_handle(); }

inline RuntimeEntry* runtime_entry(Handle handle) {
    auto it = runtimes().find(handle);
    return it == runtimes().end() ? nullptr : &it->second;
}

inline ContextEntry* context_entry(Handle handle) {
    auto it = contexts().find(handle);
    return it == contexts().end() ? nullptr : &it->second;
}

inline JSRuntime* rt_of(Handle handle) {
    auto* entry = runtime_entry(handle);
    return entry ? entry->runtime : nullptr;
}

inline JSContext* ctx_of(Handle handle) {
    auto* entry = context_entry(handle);
    return entry ? entry->context : nullptr;
}

inline Handle runtime_of_context(Handle handle) {
    auto* entry = context_entry(handle);
    return entry ? entry->runtime_owner : 0;
}

inline Handle resource_context(Handle handle) {
    auto* entry = context_entry(handle);
    return entry ? entry->resource_owner : 0;
}

inline bool owns_runtime(Handle context, Handle runtime) {
    return context != 0 && runtime_of_context(context) == runtime;
}

inline ValueEntry* value_entry(Handle handle) {
    auto it = values().find(handle);
    return it == values().end() ? nullptr : &it->second;
}

inline ValueEntry* value_entry_for_context(Handle handle, Handle context) {
    auto* entry = value_entry(handle);
    return entry && entry->runtime_owner == runtime_of_context(context) &&
            entry->context_owner == resource_context(context) ? entry : nullptr;
}

inline AtomEntry* atom_entry_for_context(Handle handle, Handle context) {
    auto it = atoms().find(handle);
    return it != atoms().end() && it->second.runtime_owner == runtime_of_context(context) &&
            it->second.context_owner == resource_context(context) ? &it->second : nullptr;
}

inline ClassIdEntry* class_entry_for_runtime(Handle handle, Handle runtime) {
    auto it = class_ids().find(handle);
    return it != class_ids().end() && it->second.runtime_owner == runtime ? &it->second : nullptr;
}

inline ModuleEntry* module_entry_for_context(Handle handle, Handle context) {
    auto it = modules().find(handle);
    return it != modules().end() && it->second.runtime_owner == runtime_of_context(context) &&
            it->second.context_owner == resource_context(context) ? &it->second : nullptr;
}

inline ModuleRegistryEntry* module_registry_entry(Handle handle) {
    auto it = module_registries().find(handle);
    return it == module_registries().end() ? nullptr : &it->second;
}

inline Handle store_value(Handle context, JSValue value) {
    if (!ctx_of(context) || JS_IsException(value)) {
        return 0;
    }
    const Handle handle = alloc_handle();
    values().emplace(handle, ValueEntry{ value, runtime_of_context(context), resource_context(context) });
    return handle;
}

inline Handle value_to_handle(JSValue value, JSContext* context) {
    for (const auto& [handle, entry] : contexts()) {
        if (entry.context == context) {
            return store_value(handle, value);
        }
    }
    return 0;
}

inline JSValueConst value_const(Handle handle, Handle context) {
    auto* entry = value_entry_for_context(handle, context);
    return entry ? entry->value : JS_UNDEFINED;
}

inline JSValue dup_value(Handle handle, Handle context) {
    auto* entry = value_entry_for_context(handle, context);
    return entry ? JS_DupValue(ctx_of(context), entry->value) : JS_UNDEFINED;
}

inline bool take_value(Handle handle, Handle context, JSValue& result) {
    auto it = values().find(handle);
    if (it == values().end() || it->second.runtime_owner != runtime_of_context(context) ||
        it->second.context_owner != resource_context(context)) {
        return false;
    }
    result = it->second.value;
    values().erase(it);
    return true;
}

inline bool free_value(Handle handle, Handle context) {
    JSValue value;
    if (!take_value(handle, context, value)) {
        return false;
    }
    JS_FreeValue(ctx_of(context), value);
    return true;
}

inline Handle store_atom(Handle context, JSAtom atom) {
    if (!ctx_of(context) || atom == JS_ATOM_NULL) {
        return 0;
    }
    const Handle handle = alloc_handle();
    atoms().emplace(handle, AtomEntry{ atom, runtime_of_context(context), resource_context(context) });
    return handle;
}

inline Handle store_pointer(Handle runtime, Handle context, void* pointer, PointerAllocator allocator) {
    if (!pointer) {
        return 0;
    }
    const Handle handle = alloc_handle();
    pointers().emplace(handle, PointerEntry{ pointer, runtime, context ? resource_context(context) : 0, allocator });
    return handle;
}

inline PointerEntry* pointer_entry(Handle handle) {
    auto it = pointers().find(handle);
    return it == pointers().end() ? nullptr : &it->second;
}

inline bool take_pointer(Handle handle, Handle runtime, Handle context, PointerEntry& result) {
    auto it = pointers().find(handle);
    if (it == pointers().end() || it->second.runtime_owner != runtime ||
        (context != 0 && it->second.context_owner != resource_context(context))) {
        return false;
    }
    result = it->second;
    pointers().erase(it);
    return true;
}

inline void cleanup_context(Handle context_handle) {
    auto* context = context_entry(context_handle);
    if (!context) return;
    const Handle owner = resource_context(context_handle);
    for (auto it = values().begin(); it != values().end();) {
        if (it->second.context_owner == owner) {
            JS_FreeValue(context->context, it->second.value);
            it = values().erase(it);
        } else ++it;
    }
    for (auto it = atoms().begin(); it != atoms().end();) {
        if (it->second.context_owner == owner) {
            JS_FreeAtom(context->context, it->second.atom);
            it = atoms().erase(it);
        } else ++it;
    }
    for (auto it = pointers().begin(); it != pointers().end();) {
        if (it->second.context_owner == owner) {
            if (it->second.allocator == PointerAllocator::Context) {
                js_free(context->context, it->second.pointer);
            }
            it = pointers().erase(it);
        } else ++it;
    }
    for (auto it = modules().begin(); it != modules().end();) {
        if (it->second.context_owner == owner) it = modules().erase(it); else ++it;
    }
}

inline void discard_context_adapters(Handle context_owner) {
    for (auto it = class_adapters().begin(); it != class_adapters().end();) {
        if (it->second.context_owner == context_owner) it = class_adapters().erase(it); else ++it;
    }
}

inline void cleanup_runtime(Handle runtime_handle) {
    auto* runtime = runtime_entry(runtime_handle);
    if (!runtime) return;
    std::vector<Handle> owned_contexts;
    for (const auto& [handle, entry] : contexts()) {
        if (entry.runtime_owner == runtime_handle) owned_contexts.push_back(handle);
    }
    for (Handle handle : owned_contexts) {
        JSContext* context = ctx_of(handle);
        cleanup_context(handle);
        contexts().erase(handle);
        JS_FreeContext(context);
    }
    for (auto it = pointers().begin(); it != pointers().end();) {
        if (it->second.runtime_owner == runtime_handle) {
            if (it->second.allocator == PointerAllocator::Runtime) {
                js_free_rt(runtime->runtime, it->second.pointer);
            }
            it = pointers().erase(it);
        } else ++it;
    }
    for (auto it = class_ids().begin(); it != class_ids().end();) {
        if (it->second.runtime_owner == runtime_handle) it = class_ids().erase(it); else ++it;
    }
    for (auto it = modules().begin(); it != modules().end();) {
        if (it->second.runtime_owner == runtime_handle) it = modules().erase(it); else ++it;
    }
    active_module_registries().erase(runtime_handle);
    for (auto it = module_registries().begin(); it != module_registries().end();) {
        if (it->second.runtime_owner == runtime_handle) it = module_registries().erase(it); else ++it;
    }
    JS_SetInterruptHandler(runtime->runtime, nullptr, nullptr);
    JS_SetHostPromiseRejectionTracker(runtime->runtime, nullptr, nullptr);
    JS_SetPromiseHook(runtime->runtime, nullptr, nullptr);
    host_callbacks().erase(runtime->runtime);
}

inline void discard_context_registrations(Handle context_owner) {
    for (auto it = gml_funcs().begin(); it != gml_funcs().end();) {
        if (it->second.context_owner == context_owner) it = gml_funcs().erase(it); else ++it;
    }
}

inline void discard_runtime_registrations(Handle runtime_handle) {
    for (auto it = gml_funcs().begin(); it != gml_funcs().end();) {
        if (it->second.runtime_owner == runtime_handle) it = gml_funcs().erase(it); else ++it;
    }
    for (auto it = callback_entries().begin(); it != callback_entries().end();) {
        if (it->second.runtime_owner == runtime_handle) it = callback_entries().erase(it); else ++it;
    }
    for (auto it = class_adapters().begin(); it != class_adapters().end();) {
        if (it->second.runtime_owner == runtime_handle) it = class_adapters().erase(it); else ++it;
    }
}

JSValue gml_trampoline(JSContext*, JSValueConst, int, JSValueConst*, int, JSValueConst*);
int qjs_interrupt_handler(JSRuntime*, void*);
void qjs_promise_rejection_tracker(JSContext*, JSValueConst, JSValueConst, bool, void*);
void qjs_promise_hook(JSContext*, JSPromiseHookType, JSValueConst, JSValueConst, void*);

} // namespace iqjs
