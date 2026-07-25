#include "native/IQuickJSInternal_native.h"
#include "iqjs_handles.h"

#include <algorithm>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

using namespace iqjs;

namespace {

template <class Enum>
int enum_int(Enum value) {
    return static_cast<int>(value);
}

ValueEntry* context_value(Handle value, Handle context) {
    auto* entry = value_entry(value);
    return entry && ctx_of(context) && entry->runtime_owner == runtime_of_context(context) &&
            entry->context_owner == resource_context(context)
        ? entry
        : nullptr;
}

AtomEntry* context_atom(Handle atom, Handle context) {
    auto it = atoms().find(atom);
    return it != atoms().end() && ctx_of(context) &&
            it->second.runtime_owner == runtime_of_context(context) &&
            it->second.context_owner == resource_context(context)
        ? &it->second
        : nullptr;
}

ClassIdEntry* context_class(Handle class_id, Handle context) {
    return ctx_of(context) ? class_entry_for_runtime(class_id, runtime_of_context(context)) : nullptr;
}

bool count_fits_int(size_t count) {
    return count <= static_cast<size_t>(std::numeric_limits<int>::max());
}

bool borrowed_values(Handle context, const std::vector<Handle>& handles,
                     std::vector<JSValue>& output) {
    if (!ctx_of(context) || !count_fits_int(handles.size())) return false;
    output.clear();
    output.reserve(handles.size());
    for (Handle handle : handles) {
        auto* entry = context_value(handle, context);
        if (!entry) {
            output.clear();
            return false;
        }
        output.push_back(entry->value);
    }
    return true;
}

bool consumed_values(Handle context, const std::vector<Handle>& handles,
                     std::vector<JSValue>& output) {
    if (!ctx_of(context) || !count_fits_int(handles.size())) return false;
    std::unordered_set<Handle> unique;
    unique.reserve(handles.size());
    for (Handle handle : handles) {
        if (!context_value(handle, context) || !unique.insert(handle).second) return false;
    }
    output.clear();
    output.reserve(handles.size());
    for (Handle handle : handles) {
        JSValue value;
        if (!take_value(handle, context, value)) return false;
        output.push_back(value);
    }
    return true;
}

Handle stored(Handle context, JSValue value) {
    return store_value(context, value);
}

JSEvalOptions eval_options(const gm_structs::IQJSEvalOptions& input,
                           const std::string& filename) {
    return JSEvalOptions{
        input.version,
        enum_int(input.eval_flags),
        filename.c_str(),
        input.line_num,
    };
}

Handle pointer_handle_for(ValueEntry* object, void* pointer) {
    if (!object || !pointer) return 0;
    for (const auto& [handle, entry] : pointers()) {
        if (entry.pointer == pointer && entry.runtime_owner == object->runtime_owner &&
            (entry.context_owner == 0 || entry.context_owner == object->context_owner)) {
            return handle;
        }
    }
    return 0;
}

Handle class_handle_for(ValueEntry* object, JSClassID class_id) {
    if (!object || class_id == JS_INVALID_CLASS_ID) return 0;
    for (const auto& [handle, entry] : class_ids()) {
        if (entry.runtime_owner == object->runtime_owner && entry.class_id == class_id) return handle;
    }
    Handle handle = alloc_handle();
    class_ids().emplace(handle, ClassIdEntry{ class_id, object->runtime_owner });
    return handle;
}

} // namespace

std::uint64_t iqjs_new_object(std::uint64_t context) {
    auto* ctx = ctx_of(context);
    return ctx ? stored(context, JS_NewObject(ctx)) : 0;
}

std::uint64_t iqjs_new_object_proto(std::uint64_t context, std::uint64_t proto) {
    auto* ctx = ctx_of(context);
    auto* proto_entry = context_value(proto, context);
    return ctx && proto_entry ? stored(context, JS_NewObjectProto(ctx, proto_entry->value)) : 0;
}

std::uint64_t iqjs_new_object_class(std::uint64_t context, std::uint64_t class_id) {
    auto* ctx = ctx_of(context);
    auto* class_entry = context_class(class_id, context);
    return ctx && class_entry ? stored(context, JS_NewObjectClass(ctx, class_entry->class_id)) : 0;
}

std::uint64_t iqjs_new_object_proto_class(std::uint64_t context, std::uint64_t proto,
                                          std::uint64_t class_id) {
    auto* ctx = ctx_of(context);
    auto* proto_entry = context_value(proto, context);
    auto* class_entry = context_class(class_id, context);
    return ctx && proto_entry && class_entry
        ? stored(context, JS_NewObjectProtoClass(ctx, proto_entry->value, class_entry->class_id))
        : 0;
}

std::uint64_t iqjs_new_object_from(std::uint64_t context,
                                   const std::vector<std::uint64_t>& atom_handles,
                                   const std::vector<std::uint64_t>& value_handles) {
    auto* ctx = ctx_of(context);
    if (!ctx || atom_handles.size() != value_handles.size() || !count_fits_int(atom_handles.size())) return 0;
    std::vector<JSAtom> native_atoms;
    native_atoms.reserve(atom_handles.size());
    for (Handle atom : atom_handles) {
        auto* entry = context_atom(atom, context);
        if (!entry) return 0;
        native_atoms.push_back(entry->atom);
    }
    std::vector<JSValue> native_values;
    if (!consumed_values(context, value_handles, native_values)) return 0;
    return stored(context, JS_NewObjectFrom(ctx, static_cast<int>(native_values.size()),
                                            native_atoms.data(), native_values.data()));
}

std::uint64_t iqjs_new_object_from_str(std::uint64_t context,
                                       const std::vector<std::string_view>& names,
                                       const std::vector<std::uint64_t>& value_handles) {
    auto* ctx = ctx_of(context);
    if (!ctx || names.size() != value_handles.size() || !count_fits_int(names.size())) return 0;
    std::vector<std::string> strings;
    std::vector<const char*> native_names;
    strings.reserve(names.size());
    native_names.reserve(names.size());
    for (std::string_view name : names) strings.emplace_back(name);
    for (const std::string& name : strings) native_names.push_back(name.c_str());
    std::vector<JSValue> native_values;
    if (!consumed_values(context, value_handles, native_values)) return 0;
    return stored(context, JS_NewObjectFromStr(ctx, static_cast<int>(native_values.size()),
                                               native_names.data(), native_values.data()));
}

std::uint64_t iqjs_to_object(std::uint64_t context, std::uint64_t value) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(value, context);
    return ctx && entry ? stored(context, JS_ToObject(ctx, entry->value)) : 0;
}

std::uint64_t iqjs_to_object_string(std::uint64_t context, std::uint64_t value) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(value, context);
    return ctx && entry ? stored(context, JS_ToObjectString(ctx, entry->value)) : 0;
}

std::uint64_t iqjs_new_array(std::uint64_t context) {
    auto* ctx = ctx_of(context);
    return ctx ? stored(context, JS_NewArray(ctx)) : 0;
}

std::uint64_t iqjs_new_array_from(std::uint64_t context,
                                  const std::vector<std::uint64_t>& value_handles) {
    auto* ctx = ctx_of(context);
    std::vector<JSValue> values;
    if (!ctx || !consumed_values(context, value_handles, values)) return 0;
    return stored(context, JS_NewArrayFrom(ctx, static_cast<int>(values.size()), values.data()));
}

std::uint64_t iqjs_new_date(std::uint64_t context, float epoch_ms) {
    auto* ctx = ctx_of(context);
    return ctx ? stored(context, JS_NewDate(ctx, epoch_ms)) : 0;
}

std::uint64_t iqjs_new_proxy(std::uint64_t context, std::uint64_t target,
                             std::uint64_t handler) {
    auto* ctx = ctx_of(context);
    auto* target_entry = context_value(target, context);
    auto* handler_entry = context_value(handler, context);
    return ctx && target_entry && handler_entry
        ? stored(context, JS_NewProxy(ctx, target_entry->value, handler_entry->value))
        : 0;
}

std::uint64_t iqjs_get_proxy_target(std::uint64_t context, std::uint64_t proxy) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(proxy, context);
    return ctx && entry ? stored(context, JS_GetProxyTarget(ctx, entry->value)) : 0;
}

std::uint64_t iqjs_get_proxy_handler(std::uint64_t context, std::uint64_t proxy) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(proxy, context);
    return ctx && entry ? stored(context, JS_GetProxyHandler(ctx, entry->value)) : 0;
}

bool iqjs_is_function(std::uint64_t context, std::uint64_t value) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(value, context);
    return ctx && entry && JS_IsFunction(ctx, entry->value);
}

bool iqjs_is_constructor(std::uint64_t context, std::uint64_t value) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(value, context);
    return ctx && entry && JS_IsConstructor(ctx, entry->value);
}

bool iqjs_set_constructor_bit(std::uint64_t context, std::uint64_t value, bool enabled) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(value, context);
    return ctx && entry && JS_SetConstructorBit(ctx, entry->value, enabled);
}

#define IQJS_OBJECT_PREDICATE(name, api) \
    bool name(std::uint64_t value) { auto* entry = value_entry(value); return entry && api(entry->value); }
IQJS_OBJECT_PREDICATE(iqjs_is_async_function, JS_IsAsyncFunction)
IQJS_OBJECT_PREDICATE(iqjs_is_regexp, JS_IsRegExp)
IQJS_OBJECT_PREDICATE(iqjs_is_map, JS_IsMap)
IQJS_OBJECT_PREDICATE(iqjs_is_set, JS_IsSet)
IQJS_OBJECT_PREDICATE(iqjs_is_weak_ref, JS_IsWeakRef)
IQJS_OBJECT_PREDICATE(iqjs_is_weak_set, JS_IsWeakSet)
IQJS_OBJECT_PREDICATE(iqjs_is_weak_map, JS_IsWeakMap)
IQJS_OBJECT_PREDICATE(iqjs_is_data_view, JS_IsDataView)
IQJS_OBJECT_PREDICATE(iqjs_is_array, JS_IsArray)
IQJS_OBJECT_PREDICATE(iqjs_is_proxy, JS_IsProxy)
IQJS_OBJECT_PREDICATE(iqjs_is_date, JS_IsDate)
#undef IQJS_OBJECT_PREDICATE

#define IQJS_GET_PROPERTY(name, key_type, key_expr, api) \
    std::uint64_t name(std::uint64_t context, std::uint64_t object, key_type key) { \
        auto* ctx = ctx_of(context); auto* entry = context_value(object, context); \
        return ctx && entry ? stored(context, api(ctx, entry->value, key_expr)) : 0; \
    }
IQJS_GET_PROPERTY(iqjs_get_property_uint32, std::uint32_t, key, JS_GetPropertyUint32)
IQJS_GET_PROPERTY(iqjs_get_property_int64, std::int64_t, key, JS_GetPropertyInt64)
#undef IQJS_GET_PROPERTY

std::uint64_t iqjs_get_property(std::uint64_t context, std::uint64_t object,
                                std::uint64_t atom) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    return ctx && object_entry && atom_entry
        ? stored(context, JS_GetProperty(ctx, object_entry->value, atom_entry->atom))
        : 0;
}

std::uint64_t iqjs_get_property_str(std::uint64_t context, std::uint64_t object,
                                    std::string_view name) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    if (!ctx || !entry) return 0;
    std::string property(name);
    return stored(context, JS_GetPropertyStr(ctx, entry->value, property.c_str()));
}

template <class Setter>
std::int32_t set_property(Handle context, Handle object, Handle value, Setter setter) {
    auto* object_entry = context_value(object, context);
    if (!object_entry || !context_value(value, context)) return -1;
    JSValue native_value;
    if (!take_value(value, context, native_value)) return -1;
    return setter(ctx_of(context), object_entry->value, native_value);
}

std::int32_t iqjs_set_property(std::uint64_t context, std::uint64_t object,
                               std::uint64_t atom, std::uint64_t value) {
    auto* atom_entry = context_atom(atom, context);
    if (!atom_entry) return -1;
    JSAtom native_atom = atom_entry->atom;
    return set_property(context, object, value,
        [native_atom](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_SetProperty(ctx, obj, native_atom, val);
        });
}

std::int32_t iqjs_set_property_uint32(std::uint64_t context, std::uint64_t object,
                                      std::uint32_t index, std::uint64_t value) {
    return set_property(context, object, value,
        [index](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_SetPropertyUint32(ctx, obj, index, val);
        });
}

std::int32_t iqjs_set_property_int64(std::uint64_t context, std::uint64_t object,
                                     std::int64_t index, std::uint64_t value) {
    return set_property(context, object, value,
        [index](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_SetPropertyInt64(ctx, obj, index, val);
        });
}

std::int32_t iqjs_set_property_str(std::uint64_t context, std::uint64_t object,
                                   std::string_view name, std::uint64_t value) {
    std::string property(name);
    return set_property(context, object, value,
        [&property](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_SetPropertyStr(ctx, obj, property.c_str(), val);
        });
}

std::int32_t iqjs_has_property(std::uint64_t context, std::uint64_t object,
                               std::uint64_t atom) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    return ctx && object_entry && atom_entry
        ? JS_HasProperty(ctx, object_entry->value, atom_entry->atom)
        : -1;
}

#define IQJS_OBJECT_STATUS(name, api) \
    std::int32_t name(std::uint64_t context, std::uint64_t object) { \
        auto* ctx = ctx_of(context); auto* entry = context_value(object, context); \
        return ctx && entry ? api(ctx, entry->value) : -1; \
    }
IQJS_OBJECT_STATUS(iqjs_is_extensible, JS_IsExtensible)
IQJS_OBJECT_STATUS(iqjs_prevent_extensions, JS_PreventExtensions)
IQJS_OBJECT_STATUS(iqjs_seal_object, JS_SealObject)
IQJS_OBJECT_STATUS(iqjs_freeze_object, JS_FreezeObject)
#undef IQJS_OBJECT_STATUS

std::int32_t iqjs_delete_property(std::uint64_t context, std::uint64_t object,
                                  std::uint64_t atom, gm_enums::IQJSPropertyFlags flags) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    return ctx && object_entry && atom_entry
        ? JS_DeleteProperty(ctx, object_entry->value, atom_entry->atom, enum_int(flags))
        : -1;
}

std::int32_t iqjs_set_prototype(std::uint64_t context, std::uint64_t object,
                                std::uint64_t proto) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* proto_entry = context_value(proto, context);
    return ctx && object_entry && proto_entry
        ? JS_SetPrototype(ctx, object_entry->value, proto_entry->value)
        : -1;
}

std::uint64_t iqjs_get_prototype(std::uint64_t context, std::uint64_t object) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    return ctx && entry ? stored(context, JS_GetPrototype(ctx, entry->value)) : 0;
}

gm_structs::IQJSInt64Result iqjs_get_length(std::uint64_t context, std::uint64_t object) {
    gm_structs::IQJSInt64Result output{ -1, 0 };
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    if (ctx && entry) output.status = JS_GetLength(ctx, entry->value, &output.value);
    return output;
}

std::int32_t iqjs_set_length(std::uint64_t context, std::uint64_t object,
                             std::int64_t length) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    return ctx && entry ? JS_SetLength(ctx, entry->value, length) : -1;
}

std::vector<gm_structs::IQJSPropertyEnumEntry> iqjs_get_own_property_names(
    std::uint64_t context, std::uint64_t object, gm_enums::IQJSGPNFlags flags) {
    std::vector<gm_structs::IQJSPropertyEnumEntry> output;
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    if (!ctx || !entry) return output;
    JSPropertyEnum* properties = nullptr;
    std::uint32_t count = 0;
    if (JS_GetOwnPropertyNames(ctx, &properties, &count, entry->value, enum_int(flags)) < 0) return output;
    output.reserve(count);
    for (std::uint32_t i = 0; i < count; ++i) {
        output.push_back(gm_structs::IQJSPropertyEnumEntry{
            properties[i].is_enumerable,
            store_atom(context, JS_DupAtom(ctx, properties[i].atom)),
        });
    }
    JS_FreePropertyEnum(ctx, properties, count);
    return output;
}

gm_structs::IQJSPropertyDescriptorResult iqjs_get_own_property(
    std::uint64_t context, std::uint64_t object, std::uint64_t atom) {
    gm_structs::IQJSPropertyDescriptorResult output{ -1, 0, 0, 0, 0 };
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    if (!ctx || !object_entry || !atom_entry) return output;
    JSPropertyDescriptor descriptor{};
    output.status = JS_GetOwnProperty(ctx, &descriptor, object_entry->value, atom_entry->atom);
    if (output.status > 0) {
        output.flags = descriptor.flags;
        output.value = stored(context, descriptor.value);
        output.getter = stored(context, descriptor.getter);
        output.setter = stored(context, descriptor.setter);
    }
    return output;
}

std::int32_t iqjs_define_property(std::uint64_t context, std::uint64_t object,
                                  std::uint64_t atom, std::uint64_t value,
                                  std::uint64_t getter, std::uint64_t setter,
                                  gm_enums::IQJSPropertyFlags flags) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    auto* value_entry = context_value(value, context);
    auto* getter_entry = context_value(getter, context);
    auto* setter_entry = context_value(setter, context);
    return ctx && object_entry && atom_entry && value_entry && getter_entry && setter_entry
        ? JS_DefineProperty(ctx, object_entry->value, atom_entry->atom, value_entry->value,
                            getter_entry->value, setter_entry->value, enum_int(flags))
        : -1;
}

template <class Definer>
std::int32_t define_property_value(Handle context, Handle object, Handle value,
                                   Definer definer) {
    auto* object_entry = context_value(object, context);
    if (!object_entry || !context_value(value, context)) return -1;
    JSValue native_value;
    if (!take_value(value, context, native_value)) return -1;
    return definer(ctx_of(context), object_entry->value, native_value);
}

std::int32_t iqjs_define_property_value(std::uint64_t context, std::uint64_t object,
                                        std::uint64_t atom, std::uint64_t value,
                                        gm_enums::IQJSPropertyFlags flags) {
    auto* atom_entry = context_atom(atom, context);
    if (!atom_entry) return -1;
    JSAtom native_atom = atom_entry->atom;
    return define_property_value(context, object, value,
        [native_atom, flags](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_DefinePropertyValue(ctx, obj, native_atom, val, enum_int(flags));
        });
}

std::int32_t iqjs_define_property_value_uint32(std::uint64_t context,
                                               std::uint64_t object,
                                               std::uint32_t index,
                                               std::uint64_t value,
                                               gm_enums::IQJSPropertyFlags flags) {
    return define_property_value(context, object, value,
        [index, flags](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_DefinePropertyValueUint32(ctx, obj, index, val, enum_int(flags));
        });
}

std::int32_t iqjs_define_property_value_str(std::uint64_t context,
                                            std::uint64_t object,
                                            std::string_view name,
                                            std::uint64_t value,
                                            gm_enums::IQJSPropertyFlags flags) {
    std::string property(name);
    return define_property_value(context, object, value,
        [&property, flags](JSContext* ctx, JSValueConst obj, JSValue val) {
            return JS_DefinePropertyValueStr(ctx, obj, property.c_str(), val, enum_int(flags));
        });
}

std::int32_t iqjs_define_property_get_set(std::uint64_t context,
                                          std::uint64_t object,
                                          std::uint64_t atom,
                                          std::uint64_t getter,
                                          std::uint64_t setter,
                                          gm_enums::IQJSPropertyFlags flags) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* atom_entry = context_atom(atom, context);
    if (!ctx || !object_entry || !atom_entry || getter == setter ||
        !context_value(getter, context) || !context_value(setter, context)) return -1;
    JSValue native_getter;
    JSValue native_setter;
    if (!take_value(getter, context, native_getter) || !take_value(setter, context, native_setter)) return -1;
    return JS_DefinePropertyGetSet(ctx, object_entry->value, atom_entry->atom,
                                   native_getter, native_setter, enum_int(flags));
}

std::int32_t iqjs_set_constructor(std::uint64_t context,
                                  std::uint64_t function_value,
                                  std::uint64_t proto) {
    auto* ctx = ctx_of(context);
    auto* function_entry = context_value(function_value, context);
    auto* proto_entry = context_value(proto, context);
    return ctx && function_entry && proto_entry
        ? JS_SetConstructor(ctx, function_entry->value, proto_entry->value)
        : -1;
}

std::int32_t iqjs_is_instance_of(std::uint64_t context, std::uint64_t value,
                                 std::uint64_t object) {
    auto* ctx = ctx_of(context);
    auto* value_entry = context_value(value, context);
    auto* object_entry = context_value(object, context);
    return ctx && value_entry && object_entry
        ? JS_IsInstanceOf(ctx, value_entry->value, object_entry->value)
        : -1;
}

void iqjs_set_is_html_dda(std::uint64_t context, std::uint64_t object) {
    auto* ctx = ctx_of(context);
    auto* entry = context_value(object, context);
    if (ctx && entry) JS_SetIsHTMLDDA(ctx, entry->value);
}

std::int32_t iqjs_unsafe_set_opaque(std::uint64_t object, std::uint64_t pointer) {
    auto* object_entry = value_entry(object);
    if (!object_entry) return -1;
    PointerEntry* pointer_entry_value = nullptr;
    if (pointer != 0) {
        pointer_entry_value = pointer_entry(pointer);
        if (!pointer_entry_value || pointer_entry_value->runtime_owner != object_entry->runtime_owner ||
            (pointer_entry_value->context_owner != 0 &&
             pointer_entry_value->context_owner != object_entry->context_owner)) return -1;
    }
    return JS_SetOpaque(object_entry->value,
                        pointer_entry_value ? pointer_entry_value->pointer : nullptr);
}

std::uint64_t iqjs_unsafe_get_opaque(std::uint64_t object, std::uint64_t class_id) {
    auto* object_entry = value_entry(object);
    auto* class_entry = object_entry
        ? class_entry_for_runtime(class_id, object_entry->runtime_owner)
        : nullptr;
    return object_entry && class_entry
        ? pointer_handle_for(object_entry, JS_GetOpaque(object_entry->value, class_entry->class_id))
        : 0;
}

std::uint64_t iqjs_unsafe_get_opaque2(std::uint64_t context, std::uint64_t object,
                                     std::uint64_t class_id) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* class_entry = context_class(class_id, context);
    return ctx && object_entry && class_entry
        ? pointer_handle_for(object_entry, JS_GetOpaque2(ctx, object_entry->value, class_entry->class_id))
        : 0;
}

gm_structs::IQJSOpaqueResult iqjs_unsafe_get_any_opaque(std::uint64_t object) {
    gm_structs::IQJSOpaqueResult output{};
    auto* object_entry = value_entry(object);
    if (!object_entry) return output;
    JSClassID class_id = JS_INVALID_CLASS_ID;
    void* pointer = JS_GetAnyOpaque(object_entry->value, &class_id);
    output.pointer = pointer_handle_for(object_entry, pointer);
    output.class_id = class_handle_for(object_entry, class_id);
    return output;
}

bool iqjs_detect_module(std::string_view source) {
    return JS_DetectModule(source.data(), source.size());
}

std::uint64_t iqjs_eval(std::uint64_t context, std::string_view source,
                        std::string_view filename, gm_enums::IQJSEvalFlags flags) {
    auto* ctx = ctx_of(context);
    if (!ctx) return 0;
    std::string input(source);
    std::string file(filename);
    return stored(context, JS_Eval(ctx, input.c_str(), input.size(), file.c_str(), enum_int(flags)));
}

std::uint64_t iqjs_eval2(std::uint64_t context, std::string_view source,
                         const gm_structs::IQJSEvalOptions& options) {
    auto* ctx = ctx_of(context);
    if (!ctx) return 0;
    std::string input(source);
    std::string filename(options.filename);
    JSEvalOptions native_options = eval_options(options, filename);
    return stored(context, JS_Eval2(ctx, input.c_str(), input.size(), &native_options));
}

std::uint64_t iqjs_eval_this(std::uint64_t context, std::uint64_t this_value,
                             std::string_view source, std::string_view filename,
                             gm_enums::IQJSEvalFlags flags) {
    auto* ctx = ctx_of(context);
    auto* this_entry = context_value(this_value, context);
    if (!ctx || !this_entry) return 0;
    std::string input(source);
    std::string file(filename);
    return stored(context, JS_EvalThis(ctx, this_entry->value, input.c_str(), input.size(),
                                       file.c_str(), enum_int(flags)));
}

std::uint64_t iqjs_eval_this2(std::uint64_t context, std::uint64_t this_value,
                              std::string_view source,
                              const gm_structs::IQJSEvalOptions& options) {
    auto* ctx = ctx_of(context);
    auto* this_entry = context_value(this_value, context);
    if (!ctx || !this_entry) return 0;
    std::string input(source);
    std::string filename(options.filename);
    JSEvalOptions native_options = eval_options(options, filename);
    return stored(context, JS_EvalThis2(ctx, this_entry->value, input.c_str(), input.size(),
                                        &native_options));
}

std::uint64_t iqjs_eval_function(std::uint64_t context,
                                 std::uint64_t function_value) {
    auto* ctx = ctx_of(context);
    if (!ctx || !context_value(function_value, context)) return 0;
    JSValue function;
    if (!take_value(function_value, context, function)) return 0;
    return stored(context, JS_EvalFunction(ctx, function));
}

std::uint64_t iqjs_get_global_object(std::uint64_t context) {
    auto* ctx = ctx_of(context);
    return ctx ? stored(context, JS_GetGlobalObject(ctx)) : 0;
}

std::uint64_t iqjs_parse_json(std::uint64_t context, std::string_view json,
                              std::string_view filename) {
    auto* ctx = ctx_of(context);
    if (!ctx) return 0;
    std::string input(json);
    std::string file(filename);
    return stored(context, JS_ParseJSON(ctx, input.c_str(), input.size(), file.c_str()));
}

std::uint64_t iqjs_json_stringify(std::uint64_t context, std::uint64_t object,
                                  std::uint64_t replacer, std::uint64_t space) {
    auto* ctx = ctx_of(context);
    auto* object_entry = context_value(object, context);
    auto* replacer_entry = context_value(replacer, context);
    auto* space_entry = context_value(space, context);
    return ctx && object_entry && replacer_entry && space_entry
        ? stored(context, JS_JSONStringify(ctx, object_entry->value, replacer_entry->value,
                                           space_entry->value))
        : 0;
}

std::uint64_t iqjs_call(std::uint64_t context, std::uint64_t function_value,
                        std::uint64_t this_value,
                        const std::vector<std::uint64_t>& arguments) {
    auto* ctx = ctx_of(context);
    auto* function_entry = context_value(function_value, context);
    auto* this_entry = context_value(this_value, context);
    std::vector<JSValue> argv;
    if (!ctx || !function_entry || !this_entry || !borrowed_values(context, arguments, argv)) return 0;
    return stored(context, JS_Call(ctx, function_entry->value, this_entry->value,
                                   static_cast<int>(argv.size()), argv.data()));
}

std::uint64_t iqjs_invoke(std::uint64_t context, std::uint64_t this_value,
                          std::uint64_t atom,
                          const std::vector<std::uint64_t>& arguments) {
    auto* ctx = ctx_of(context);
    auto* this_entry = context_value(this_value, context);
    auto* atom_entry = context_atom(atom, context);
    std::vector<JSValue> argv;
    if (!ctx || !this_entry || !atom_entry || !borrowed_values(context, arguments, argv)) return 0;
    return stored(context, JS_Invoke(ctx, this_entry->value, atom_entry->atom,
                                     static_cast<int>(argv.size()), argv.data()));
}

std::uint64_t iqjs_call_constructor(std::uint64_t context,
                                    std::uint64_t function_value,
                                    const std::vector<std::uint64_t>& arguments) {
    auto* ctx = ctx_of(context);
    auto* function_entry = context_value(function_value, context);
    std::vector<JSValue> argv;
    if (!ctx || !function_entry || !borrowed_values(context, arguments, argv)) return 0;
    return stored(context, JS_CallConstructor(ctx, function_entry->value,
                                              static_cast<int>(argv.size()), argv.data()));
}

std::uint64_t iqjs_call_constructor2(std::uint64_t context,
                                     std::uint64_t function_value,
                                     std::uint64_t new_target,
                                     const std::vector<std::uint64_t>& arguments) {
    auto* ctx = ctx_of(context);
    auto* function_entry = context_value(function_value, context);
    auto* target_entry = context_value(new_target, context);
    std::vector<JSValue> argv;
    if (!ctx || !function_entry || !target_entry ||
        !borrowed_values(context, arguments, argv)) return 0;
    return stored(context, JS_CallConstructor2(ctx, function_entry->value, target_entry->value,
                                               static_cast<int>(argv.size()), argv.data()));
}
