#include "iqjs_handles.h"

#include <algorithm>
#include <cstring>
#include <limits>
#include <vector>

using namespace iqjs;

namespace {

ValueEntry* owned_value(Handle context, Handle value)
{
    auto* entry = value_entry(value);
    return entry && entry->context_owner == resource_context(context) ? entry : nullptr;
}

Handle store_result(Handle context, JSValue value)
{
    return store_value(context, value);
}

Handle store_borrowed_pointer(Handle runtime, Handle context, void* pointer)
{
    const Handle handle = alloc_handle();
    pointers().emplace(handle,
                       PointerEntry{ pointer, runtime, resource_context(context), PointerAllocator::Borrowed });
    return handle;
}

Handle context_handle(JSRuntime* runtime, JSContext* context, Handle runtime_handle)
{
    if (!context) return 0;
    for (const auto& [handle, entry] : contexts()) {
        if (entry.runtime_owner == runtime_handle && entry.context == context &&
            JS_GetRuntime(entry.context) == runtime) {
            return handle;
        }
    }
    return 0;
}

void free_array_buffer_data(JSRuntime* runtime, void*, void* pointer)
{
    js_free_rt(runtime, pointer);
}

Handle new_owned_buffer(Handle context_handle, gm::wire::GMBuffer data,
                        bool shared, bool uint8_array)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || data.length() > std::numeric_limits<size_t>::max() ||
        (data.length() != 0 && !data.data())) {
        return 0;
    }

    const size_t length = static_cast<size_t>(data.length());
    auto* bytes = static_cast<std::uint8_t*>(js_malloc(context, length));
    if (!bytes && length != 0) return 0;
    if (length != 0) std::memcpy(bytes, data.data(), length);

    JSValue value = uint8_array
        ? JS_NewUint8Array(context, bytes, length, free_array_buffer_data, nullptr, shared)
        : JS_NewArrayBuffer(context, bytes, length, free_array_buffer_data, nullptr, shared);
    if (JS_IsException(value)) js_free(context, bytes);
    return store_result(context_handle, value);
}

std::vector<std::uint8_t> copy_bytes(JSContext* context, JSValueConst value,
                                     bool uint8_array)
{
    size_t length = 0;
    std::uint8_t* bytes = uint8_array
        ? JS_GetUint8Array(context, &length, value)
        : JS_GetArrayBuffer(context, &length, value);
    if (!bytes && (length != 0 || JS_HasException(context))) return {};
    if (length == 0) return {};
    return std::vector<std::uint8_t>(bytes, bytes + length);
}

int enum_value(gm_enums::IQJSWriteObjectFlags flags)
{
    return static_cast<int>(flags);
}

int enum_value(gm_enums::IQJSReadObjectFlags flags)
{
    return static_cast<int>(flags);
}

} // namespace

std::uint64_t iqjs_new_array_buffer_copy(std::uint64_t context_handle,
                                         gm::wire::GMBuffer data)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || data.length() > std::numeric_limits<size_t>::max() ||
        (data.length() != 0 && !data.data())) {
        return 0;
    }
    return store_result(context_handle,
                        JS_NewArrayBufferCopy(context,
                            static_cast<const std::uint8_t*>(data.data()),
                            static_cast<size_t>(data.length())));
}

std::uint64_t iqjs_new_array_buffer_owned(std::uint64_t context,
                                          gm::wire::GMBuffer data, bool shared)
{
    return new_owned_buffer(context, data, shared, false);
}

void iqjs_detach_array_buffer(std::uint64_t context_handle, std::uint64_t object)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    if (context && entry) JS_DetachArrayBuffer(context, entry->value);
}

std::int64_t iqjs_copy_array_buffer(std::uint64_t context_handle,
                                    std::uint64_t object,
                                    gm::wire::GMBuffer destination)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    if (!context || !entry || destination.length() > std::numeric_limits<size_t>::max() ||
        (destination.length() != 0 && !destination.data())) {
        return -1;
    }
    size_t source_length = 0;
    std::uint8_t* source = JS_GetArrayBuffer(context, &source_length, entry->value);
    if (!source && (source_length != 0 || JS_HasException(context))) return -1;
    const size_t copied = std::min(source_length, static_cast<size_t>(destination.length()));
    if (copied != 0) std::memcpy(destination.data(), source, copied);
    return static_cast<std::int64_t>(copied);
}

std::vector<std::uint8_t> iqjs_get_array_buffer_copy(std::uint64_t context_handle,
                                                     std::uint64_t object)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    return context && entry ? copy_bytes(context, entry->value, false)
                            : std::vector<std::uint8_t>{};
}

std::int32_t iqjs_is_immutable_array_buffer(std::uint64_t object)
{
    auto* entry = value_entry(object);
    return entry ? JS_IsImmutableArrayBuffer(entry->value) : -1;
}

std::int32_t iqjs_set_immutable_array_buffer(std::uint64_t object, bool immutable)
{
    auto* entry = value_entry(object);
    return entry ? JS_SetImmutableArrayBuffer(entry->value, immutable) : -1;
}

std::vector<std::uint8_t> iqjs_get_uint8_array_copy(std::uint64_t context_handle,
                                                    std::uint64_t object)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    return context && entry ? copy_bytes(context, entry->value, true)
                            : std::vector<std::uint8_t>{};
}

std::uint64_t iqjs_new_typed_array(std::uint64_t context_handle,
                                   const std::vector<std::uint64_t>& arguments,
                                   gm_enums::IQJSTypedArrayType array_type)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || arguments.size() > static_cast<size_t>(std::numeric_limits<int>::max())) return 0;
    std::vector<JSValueConst> values;
    values.reserve(arguments.size());
    for (Handle argument : arguments) {
        auto* entry = owned_value(context_handle, argument);
        if (!entry) return 0;
        values.push_back(entry->value);
    }
    return store_result(context_handle,
                        JS_NewTypedArray(context, static_cast<int>(values.size()), values.data(),
                            static_cast<JSTypedArrayEnum>(array_type)));
}

gm_structs::IQJSTypedArrayBufferInfo iqjs_get_typed_array_buffer(
    std::uint64_t context_handle, std::uint64_t object)
{
    gm_structs::IQJSTypedArrayBufferInfo output{};
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    if (!context || !entry) return output;
    size_t offset = 0, length = 0, element_size = 0;
    JSValue buffer = JS_GetTypedArrayBuffer(context, entry->value, &offset, &length, &element_size);
    output.buffer = store_result(context_handle, buffer);
    output.byte_offset = offset;
    output.byte_length = length;
    output.bytes_per_element = element_size;
    return output;
}

std::uint64_t iqjs_new_uint8_array_copy(std::uint64_t context_handle,
                                        gm::wire::GMBuffer data)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || data.length() > std::numeric_limits<size_t>::max() ||
        (data.length() != 0 && !data.data())) {
        return 0;
    }
    return store_result(context_handle,
                        JS_NewUint8ArrayCopy(context,
                            static_cast<const std::uint8_t*>(data.data()),
                            static_cast<size_t>(data.length())));
}

std::uint64_t iqjs_new_uint8_array_owned(std::uint64_t context,
                                         gm::wire::GMBuffer data, bool shared)
{
    return new_owned_buffer(context, data, shared, true);
}

std::int32_t iqjs_get_typed_array_type(std::uint64_t object)
{
    auto* entry = value_entry(object);
    return entry ? JS_GetTypedArrayType(entry->value) : -1;
}

gm_structs::IQJSPromiseCapability iqjs_new_promise_capability(std::uint64_t context_handle)
{
    gm_structs::IQJSPromiseCapability output{};
    JSContext* context = ctx_of(context_handle);
    if (!context) return output;
    JSValue functions[2] = { JS_UNDEFINED, JS_UNDEFINED };
    JSValue promise = JS_NewPromiseCapability(context, functions);
    output.promise = store_result(context_handle, promise);
    output.resolve = store_result(context_handle, functions[0]);
    output.reject = store_result(context_handle, functions[1]);
    return output;
}

gm_enums::IQJSPromiseState iqjs_promise_state(std::uint64_t context_handle,
                                              std::uint64_t promise)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, promise);
    return context && entry
        ? static_cast<gm_enums::IQJSPromiseState>(JS_PromiseState(context, entry->value))
        : gm_enums::IQJSPromiseState::NotAPromise;
}

std::uint64_t iqjs_promise_result(std::uint64_t context_handle,
                                  std::uint64_t promise)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, promise);
    return context && entry
        ? store_result(context_handle, JS_PromiseResult(context, entry->value))
        : 0;
}

std::uint64_t iqjs_new_settled_promise(std::uint64_t context_handle,
                                       bool reject, std::uint64_t value)
{
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, value);
    return context && entry
        ? store_result(context_handle, JS_NewSettledPromise(context, reject, entry->value))
        : 0;
}

bool iqjs_is_job_pending(std::uint64_t runtime_handle)
{
    JSRuntime* runtime = rt_of(runtime_handle);
    return runtime && JS_IsJobPending(runtime);
}

std::uint64_t iqjs_get_pending_job_context(std::uint64_t runtime_handle)
{
    JSRuntime* runtime = rt_of(runtime_handle);
    return runtime ? context_handle(runtime, JS_GetPendingJobContext(runtime), runtime_handle) : 0;
}

gm_structs::IQJSJobResult iqjs_execute_pending_job(std::uint64_t runtime_handle)
{
    gm_structs::IQJSJobResult output{ -1, 0 };
    JSRuntime* runtime = rt_of(runtime_handle);
    if (!runtime) return output;
    JSContext* context = nullptr;
    output.status = JS_ExecutePendingJob(runtime, &context);
    output.context = context_handle(runtime, context, runtime_handle);
    return output;
}

std::vector<std::uint8_t> iqjs_write_object(std::uint64_t context_handle,
                                            std::uint64_t object,
                                            gm_enums::IQJSWriteObjectFlags flags)
{
    std::vector<std::uint8_t> output;
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    if (!context || !entry) return output;
    size_t length = 0;
    std::uint8_t* bytes = JS_WriteObject(context, &length, entry->value, enum_value(flags));
    if (bytes) output.assign(bytes, bytes + length);
    js_free(context, bytes);
    return output;
}

gm_structs::IQJSSerializedObject iqjs_unsafe_write_object2(
    std::uint64_t context_handle, std::uint64_t object,
    gm_enums::IQJSWriteObjectFlags flags)
{
    gm_structs::IQJSSerializedObject output;
    JSContext* context = ctx_of(context_handle);
    auto* entry = owned_value(context_handle, object);
    if (!context || !entry) return output;
    size_t length = 0;
    JSSABTab sab{};
    std::uint8_t* bytes = JS_WriteObject2(context, &length, entry->value, enum_value(flags), &sab);
    if (bytes) output.bytes.assign(bytes, bytes + length);
    if (bytes) {
        const Handle runtime_handle = runtime_of_context(context_handle);
        output.shared_array_buffer_pointers.reserve(sab.len);
        for (size_t i = 0; i < sab.len; ++i) {
            output.shared_array_buffer_pointers.push_back(
                store_borrowed_pointer(runtime_handle, context_handle, sab.tab[i]));
        }
    }
    js_free(context, sab.tab);
    js_free(context, bytes);
    return output;
}

std::uint64_t iqjs_read_object(std::uint64_t context_handle, gm::wire::GMBuffer data,
                               gm_enums::IQJSReadObjectFlags flags)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || data.length() > std::numeric_limits<size_t>::max() ||
        (data.length() != 0 && !data.data())) {
        return 0;
    }
    return store_result(context_handle,
                        JS_ReadObject(context, static_cast<const std::uint8_t*>(data.data()),
                                      static_cast<size_t>(data.length()), enum_value(flags)));
}

std::uint64_t iqjs_unsafe_read_object2(
    std::uint64_t context_handle, gm::wire::GMBuffer data,
    gm_enums::IQJSReadObjectFlags flags,
    const std::vector<std::uint64_t>& shared_array_buffer_pointers)
{
    JSContext* context = ctx_of(context_handle);
    if (!context || data.length() > std::numeric_limits<size_t>::max() ||
        (data.length() != 0 && !data.data())) {
        return 0;
    }
    std::vector<void*> expected;
    expected.reserve(shared_array_buffer_pointers.size());
    for (Handle handle : shared_array_buffer_pointers) {
        auto* pointer = pointer_entry(handle);
        if (!pointer || pointer->runtime_owner != runtime_of_context(context_handle) ||
            pointer->context_owner != resource_context(context_handle) ||
            pointer->allocator != PointerAllocator::Borrowed) {
            return 0;
        }
        expected.push_back(pointer->pointer);
    }

    JSSABTab sab{};
    JSValue value = JS_ReadObject2(context, static_cast<const std::uint8_t*>(data.data()),
                                   static_cast<size_t>(data.length()), enum_value(flags), &sab);
    bool matches = sab.len == expected.size();
    for (size_t i = 0; matches && i < sab.len; ++i) matches = sab.tab[i] == expected[i];
    js_free(context, sab.tab);
    if (!matches) {
        JS_FreeValue(context, value);
        return store_result(context_handle,
                            JS_ThrowTypeError(context, "SharedArrayBuffer pointer tokens do not match"));
    }
    return store_result(context_handle, value);
}
