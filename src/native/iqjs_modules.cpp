#include "native/IQuickJSInternal_native.h"
#include "iqjs_handles.h"

#include <limits>
#include <string>
#include <vector>

using namespace iqjs;

namespace {

Handle registry_handle(void* opaque)
{
    return static_cast<Handle>(reinterpret_cast<std::uintptr_t>(opaque));
}

void* registry_opaque(Handle handle)
{
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(handle));
}

JSModuleDef* load_registry_module(JSContext* ctx, const char* module_name, void* opaque)
{
    std::string source;
    {
        std::lock_guard<TableMutex> lock(table_mutex());
        auto* registry = module_registry_entry(registry_handle(opaque));
        if (!registry || rt_of(registry->runtime_owner) != JS_GetRuntime(ctx)) {
            JS_ThrowReferenceError(ctx, "module registry is no longer available");
            return nullptr;
        }
        auto it = registry->sources.find(module_name);
        if (it == registry->sources.end()) {
            JS_ThrowReferenceError(ctx, "module '%s' is not registered", module_name);
            return nullptr;
        }
        source = it->second;
    }

    JSValue compiled = JS_Eval(ctx, source.c_str(), source.size(), module_name,
        JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    if (JS_IsException(compiled)) {
        return nullptr;
    }
    auto* module = static_cast<JSModuleDef*>(JS_VALUE_GET_PTR(compiled));
    JS_FreeValue(ctx, compiled);
    return module;
}

JSModuleDef* module_loader(JSContext* ctx, const char* module_name, void* opaque)
{
    return load_registry_module(ctx, module_name, opaque);
}

JSModuleDef* module_loader_with_attributes(JSContext* ctx, const char* module_name,
    void* opaque, JSValueConst)
{
    return load_registry_module(ctx, module_name, opaque);
}

int check_module_attributes(JSContext* ctx, void* opaque, JSValueConst attributes)
{
    if (JS_IsUndefined(attributes)) {
        return 0;
    }

    JSPropertyEnum* properties = nullptr;
    uint32_t count = 0;
    if (JS_GetOwnPropertyNames(ctx, &properties, &count, attributes,
            JS_GPN_STRING_MASK | JS_GPN_ENUM_ONLY) < 0) {
        return -1;
    }

    for (uint32_t i = 0; i < count; ++i) {
        const char* name = JS_AtomToCString(ctx, properties[i].atom);
        if (!name) {
            JS_FreePropertyEnum(ctx, properties, count);
            return -1;
        }
        bool supported = false;
        {
            std::lock_guard<TableMutex> lock(table_mutex());
            auto* registry = module_registry_entry(registry_handle(opaque));
            supported = registry && rt_of(registry->runtime_owner) == JS_GetRuntime(ctx) &&
                registry->supported_attributes.find(name) != registry->supported_attributes.end();
        }
        if (!supported) {
            JS_ThrowTypeError(ctx, "unsupported module attribute: '%s'", name);
            JS_FreeCString(ctx, name);
            JS_FreePropertyEnum(ctx, properties, count);
            return -1;
        }
        JS_FreeCString(ctx, name);
    }
    JS_FreePropertyEnum(ctx, properties, count);
    return 0;
}

int empty_c_module_init(JSContext*, JSModuleDef*)
{
    return 0;
}

bool supported_function_list_type(int type)
{
    switch (type) {
    case JS_DEF_PROP_STRING:
    case JS_DEF_PROP_INT32:
    case JS_DEF_PROP_INT64:
    case JS_DEF_PROP_DOUBLE:
    case JS_DEF_PROP_UNDEFINED:
    case JS_DEF_PROP_BOOL:
        return true;
    default:
        return false;
    }
}

int validate_function_list(JSContext* ctx, const std::vector<gm_structs::IQJSFunctionListEntry>& entries)
{
    for (const auto& entry : entries) {
        if (!supported_function_list_type(entry.definition_type)) {
            JS_ThrowTypeError(ctx, "unsupported function-list entry type %d for '%s'",
                entry.definition_type, entry.name.c_str());
            return -1;
        }
        if (entry.definition_type == JS_DEF_PROP_INT32 &&
            (entry.integer_value < std::numeric_limits<int32_t>::min() ||
                entry.integer_value > std::numeric_limits<int32_t>::max())) {
            JS_ThrowTypeError(ctx, "function-list int32 value is out of range for '%s'",
                entry.name.c_str());
            return -1;
        }
    }
    return 0;
}

JSValue function_list_value(JSContext* ctx, const gm_structs::IQJSFunctionListEntry& entry)
{
    switch (entry.definition_type) {
    case JS_DEF_PROP_STRING:
        return JS_NewStringLen(ctx, entry.string_value.data(), entry.string_value.size());
    case JS_DEF_PROP_INT32:
        return JS_NewInt32(ctx, static_cast<int32_t>(entry.integer_value));
    case JS_DEF_PROP_INT64:
        return JS_NewInt64(ctx, entry.integer_value);
    case JS_DEF_PROP_DOUBLE:
        return JS_NewFloat64(ctx, entry.float_value);
    case JS_DEF_PROP_UNDEFINED:
        return JS_UNDEFINED;
    case JS_DEF_PROP_BOOL:
        return JS_NewBool(ctx, entry.integer_value != 0);
    default:
        return JS_EXCEPTION;
    }
}

Handle store_module(Handle context, JSModuleDef* module)
{
    if (!module) {
        return 0;
    }
    Handle handle = alloc_handle();
    modules().emplace(handle, ModuleEntry{ module, runtime_of_context(context), resource_context(context) });
    return handle;
}

} // namespace

std::uint64_t iqjs_module_registry_create(std::uint64_t rt)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    if (!rt_of(rt)) {
        return 0;
    }
    Handle handle = alloc_handle();
    module_registries().emplace(handle, ModuleRegistryEntry{ rt, {}, {} });
    return handle;
}

void iqjs_module_registry_add(std::uint64_t registry, std::string_view name, std::string_view source)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    if (auto* entry = module_registry_entry(registry)) {
        entry->sources[std::string(name)] = std::string(source);
    }
}

void iqjs_module_registry_remove(std::uint64_t registry, std::string_view name)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    if (auto* entry = module_registry_entry(registry)) {
        entry->sources.erase(std::string(name));
    }
}

void iqjs_module_registry_set_supported_attributes(std::uint64_t registry,
    const std::vector<std::string_view>& attributes)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    auto* entry = module_registry_entry(registry);
    if (!entry) {
        return;
    }
    entry->supported_attributes.clear();
    for (std::string_view attribute : attributes) {
        entry->supported_attributes.emplace(attribute);
    }
}

void iqjs_module_registry_install(std::uint64_t rt, std::uint64_t registry, bool attributes_aware)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSRuntime* runtime = rt_of(rt);
    auto* entry = module_registry_entry(registry);
    if (!runtime || !entry || entry->runtime_owner != rt) {
        return;
    }
    active_module_registries()[rt] = registry;
    if (attributes_aware) {
        JS_SetModuleLoaderFunc2(runtime, nullptr, module_loader_with_attributes,
            check_module_attributes, registry_opaque(registry));
    } else {
        JS_SetModuleLoaderFunc(runtime, nullptr, module_loader, registry_opaque(registry));
    }
}

void iqjs_module_registry_free(std::uint64_t registry)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    auto* entry = module_registry_entry(registry);
    if (!entry) {
        return;
    }
    Handle runtime_handle = entry->runtime_owner;
    auto active = active_module_registries().find(runtime_handle);
    if (active != active_module_registries().end() && active->second == registry) {
        if (JSRuntime* runtime = rt_of(runtime_handle)) {
            JS_SetModuleLoaderFunc(runtime, nullptr, nullptr, nullptr);
        }
        active_module_registries().erase(active);
    }
    module_registries().erase(registry);
}

std::uint64_t iqjs_get_import_meta(std::uint64_t ctx, std::uint64_t module_handle)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    return context && module ? store_value(ctx, JS_GetImportMeta(context, module->module)) : 0;
}

std::uint64_t iqjs_get_module_name(std::uint64_t ctx, std::uint64_t module_handle)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    return context && module ? store_atom(ctx, JS_GetModuleName(context, module->module)) : 0;
}

std::uint64_t iqjs_get_module_namespace(std::uint64_t ctx, std::uint64_t module_handle)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    return context && module ? store_value(ctx, JS_GetModuleNamespace(context, module->module)) : 0;
}

std::int32_t iqjs_set_module_private_value(std::uint64_t ctx, std::uint64_t module_handle,
    std::uint64_t value)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    JSValue owned;
    if (!context || !module || !take_value(value, ctx, owned)) {
        return -1;
    }
    return JS_SetModulePrivateValue(context, module->module, owned);
}

std::uint64_t iqjs_get_module_private_value(std::uint64_t ctx, std::uint64_t module_handle)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    return context && module ? store_value(ctx, JS_GetModulePrivateValue(context, module->module)) : 0;
}

std::uint64_t iqjs_load_module(std::uint64_t ctx, std::string_view basename, std::string_view filename)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    if (!context) {
        return 0;
    }
    std::string base(basename);
    std::string file(filename);
    return store_value(ctx, JS_LoadModule(context, base.c_str(), file.c_str()));
}

std::int32_t iqjs_resolve_module(std::uint64_t ctx, std::uint64_t object)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* value = value_entry_for_context(object, ctx);
    return context && value ? JS_ResolveModule(context, value->value) : -1;
}

std::uint64_t iqjs_get_script_or_module_name(std::uint64_t ctx, std::int32_t levels)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    if (!context) {
        return 0;
    }
    JSAtom atom = JS_GetScriptOrModuleName(context, levels);
    return atom == JS_ATOM_NULL ? 0 : store_atom(ctx, atom);
}

std::uint64_t iqjs_new_c_module_adapter(std::uint64_t ctx, std::string_view name,
    const std::vector<std::string_view>& export_names)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    if (!context) {
        return 0;
    }
    std::string module_name(name);
    JSModuleDef* module = JS_NewCModule(context, module_name.c_str(), empty_c_module_init);
    if (!module) {
        return 0;
    }
    for (std::string_view export_name : export_names) {
        std::string text(export_name);
        if (JS_AddModuleExport(context, module, text.c_str()) < 0) {
            return 0;
        }
    }
    return store_module(ctx, module);
}

std::int32_t iqjs_add_module_export(std::uint64_t ctx, std::uint64_t module_handle,
    std::string_view name)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    std::string text(name);
    return context && module ? JS_AddModuleExport(context, module->module, text.c_str()) : -1;
}

std::int32_t iqjs_set_module_export(std::uint64_t ctx, std::uint64_t module_handle,
    std::string_view name, std::uint64_t value)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    JSValue owned;
    if (!context || !module || !take_value(value, ctx, owned)) {
        return -1;
    }
    std::string text(name);
    return JS_SetModuleExport(context, module->module, text.c_str(), owned);
}

std::int32_t iqjs_set_property_function_list_adapter(std::uint64_t ctx, std::uint64_t object,
    const std::vector<gm_structs::IQJSFunctionListEntry>& entries)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* target = value_entry_for_context(object, ctx);
    if (!context || !target || validate_function_list(context, entries) < 0) {
        return -1;
    }
    for (const auto& entry : entries) {
        JSValue value = function_list_value(context, entry);
        if (JS_IsException(value) || JS_DefinePropertyValueStr(context, target->value,
                entry.name.c_str(), value, entry.property_flags) < 0) {
            return -1;
        }
    }
    return 0;
}

std::int32_t iqjs_add_module_export_list_adapter(std::uint64_t ctx,
    std::uint64_t module_handle, const std::vector<gm_structs::IQJSFunctionListEntry>& entries)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    if (!context || !module || validate_function_list(context, entries) < 0) {
        return -1;
    }
    for (const auto& entry : entries) {
        if (JS_AddModuleExport(context, module->module, entry.name.c_str()) < 0) {
            return -1;
        }
    }
    return 0;
}

std::int32_t iqjs_set_module_export_list_adapter(std::uint64_t ctx,
    std::uint64_t module_handle, const std::vector<gm_structs::IQJSFunctionListEntry>& entries)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* context = ctx_of(ctx);
    auto* module = module_entry_for_context(module_handle, ctx);
    if (!context || !module || validate_function_list(context, entries) < 0) {
        return -1;
    }
    for (const auto& entry : entries) {
        JSValue value = function_list_value(context, entry);
        if (JS_IsException(value) ||
            JS_SetModuleExport(context, module->module, entry.name.c_str(), value) < 0) {
            return -1;
        }
    }
    return 0;
}
