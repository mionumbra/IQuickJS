// ##### extgen :: Auto-generated file do not edit!! #####

#include "IQuickJSInternal_native.h"
#include "IQuickJSInternal_exports.h"

using namespace gm_structs;
using namespace gm::wire::codec;

static gm::runtime::DispatchQueue __dispatch_queue;

// Internal function used for fetching dispatched function calls to GML
GMEXPORT double __EXT_NATIVE__IQuickJS_invocation_handler(char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferWriter __bw{ __ret_buffer, static_cast<size_t>(__ret_buffer_length) };
    return __dispatch_queue.fetch(__bw);
}

static std::queue<gm::wire::GMBuffer> __buffer_queue;

// Internal function used for queueing buffers to native code
GMEXPORT double __EXT_NATIVE__IQuickJS_queue_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::wire::GMBuffer __buff{__arg_buffer, static_cast<uint64_t>(__arg_buffer_length)};
    __buffer_queue.push(__buff);

    return 1.0;
}

GMEXPORT double __EXT_NATIVE__iqjs_init()
{
    iqjs_init();
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_shutdown()
{
    iqjs_shutdown();
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_runtime(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = iqjs_new_runtime();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_new_runtime_with_allocator(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: policy, type: String
    std::string_view policy = gm::wire::codec::readValue<std::string_view>(__br);

    // field: opaque, type: UInt64
    std::uint64_t opaque = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_new_runtime_with_allocator(policy, opaque);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_runtime(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_runtime(rt);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_runtime_info(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: info, type: String
    std::string_view info = gm::wire::codec::readValue<std::string_view>(__br);

    iqjs_set_runtime_info(rt, info);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_dump_flags(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSDumpFlags
    gm_enums::IQJSDumpFlags flags = gm::wire::codec::readValue<gm_enums::IQJSDumpFlags>(__br);

    iqjs_set_dump_flags(rt, flags);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_dump_flags(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_dump_flags(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_update_stack_top(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_update_stack_top(rt);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_run_gc(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_run_gc(rt);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_live_object(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_live_object(rt, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_can_block(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: can_block, type: Bool
    bool can_block = gm::wire::codec::readValue<bool>(__br);

    iqjs_set_can_block(rt, can_block);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_job_pending(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_job_pending(rt);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_pending_job_context(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_pending_job_context(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_execute_pending_job(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_execute_pending_job(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSJobResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT char* __EXT_NATIVE__iqjs_get_version()
{
    static std::string __result;
    __result = iqjs_get_version();
    return (char*)__result.c_str();
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_set_runtime_opaque(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_unsafe_set_runtime_opaque(rt, pointer);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_get_runtime_opaque(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_get_runtime_opaque(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_add_runtime_finalizer_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    // field: arg, type: UInt64
    std::uint64_t arg = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_runtime_finalizer_adapter(rt, callback, arg);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_remove_runtime_finalizer_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registration, type: UInt64
    std::uint64_t registration = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_remove_runtime_finalizer_adapter(registration);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_mark_value_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_mark_value_adapter(rt, value);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_context(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_context(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_context_raw(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_context_raw(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_dup_context(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_dup_context(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_context(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_context(ctx);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_runtime(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_runtime(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_set_context_opaque(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_unsafe_set_context_opaque(ctx, pointer);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_get_context_opaque(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_get_context_opaque(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_function_proto(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_function_proto(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_base_objects(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_base_objects(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_date(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_date(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_eval(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_eval(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_regexp_compiler(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_add_intrinsic_regexp_compiler(ctx);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_regexp(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_regexp(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_json(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_json(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_proxy(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_proxy(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_map_set(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_map_set(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_typed_arrays(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_typed_arrays(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_promise(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_promise(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_bigint(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_bigint(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_weak_ref(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_weak_ref(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_performance(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_performance(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_dom_exception(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_dom_exception(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_intrinsic_atob(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_add_intrinsic_atob(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_memory_limit(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: limit, type: UInt64
    std::uint64_t limit = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_memory_limit(rt, limit);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_gc_threshold(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_gc_threshold(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_gc_threshold(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: threshold, type: UInt64
    std::uint64_t threshold = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_gc_threshold(rt, threshold);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_max_stack_size(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_max_stack_size(rt, size);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_compute_memory_usage(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_compute_memory_usage(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSMemoryUsage
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT char* __EXT_NATIVE__iqjs_dump_memory_usage(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    static std::string __result;
    __result = iqjs_dump_memory_usage(rt);
    return (char*)__result.c_str();
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_calloc_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: count, type: UInt64
    std::uint64_t count = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_calloc_rt(rt, count, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_malloc_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_malloc_rt(rt, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_mallocz_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_mallocz_rt(rt, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_realloc_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_realloc_rt(rt, pointer, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_free_rt(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_unsafe_free_rt(rt, pointer);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_malloc_usable_size_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_malloc_usable_size_rt(rt, pointer);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_calloc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: count, type: UInt64
    std::uint64_t count = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_calloc(ctx, count, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_malloc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_malloc(ctx, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_mallocz(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_mallocz(ctx, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_realloc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_realloc(ctx, pointer, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_realloc2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: size, type: UInt64
    std::uint64_t size = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_realloc2(ctx, pointer, size);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSReallocResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_free(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_unsafe_free(ctx, pointer);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_malloc_usable_size(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_malloc_usable_size(ctx, pointer);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_strdup(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_unsafe_strdup(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_strndup(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    // field: byte_count, type: UInt64
    std::uint64_t byte_count = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_strndup(ctx, value, byte_count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_atom_null(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = iqjs_atom_null();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_atom(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_atom(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_atom_len(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    // field: byte_count, type: UInt64
    std::uint64_t byte_count = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_atom_len(ctx, value, byte_count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_atom_uint32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt32
    std::uint32_t value = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = iqjs_new_atom_uint32(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_dup_atom(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_dup_atom(ctx, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_dup_atom_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_dup_atom_rt(rt, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_atom(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_atom(ctx, atom);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_atom_rt(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_atom_rt(rt, atom);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_atom_to_value(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_atom_to_value(ctx, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_atom_to_string(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_atom_to_string(ctx, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT char* __EXT_NATIVE__iqjs_atom_to_cstring(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    static std::string __result;
    __result = iqjs_atom_to_cstring(ctx, atom);
    return (char*)__result.c_str();
}

GMEXPORT double __EXT_NATIVE__iqjs_value_to_atom(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_value_to_atom(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_class_id(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_class_id(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_class_id(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_class_id(value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_class_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: finalizer, type: Function
    gm::wire::GMFunction finalizer = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    // field: gc_mark, type: Function
    gm::wire::GMFunction gc_mark = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    // field: call, type: Function
    gm::wire::GMFunction call = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_new_class_adapter(rt, class_id, name, finalizer, gc_mark, call);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_registered_class(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_registered_class(rt, class_id);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_class_name(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_class_name(rt, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_class_proto(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proto, type: UInt64
    std::uint64_t proto = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_class_proto(ctx, class_id, proto);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_class_proto(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_class_proto(ctx, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_class_exotic_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: methods_object, type: UInt64
    std::uint64_t methods_object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_class_exotic_adapter(ctx, class_id, methods_object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_null(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_null(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_undefined(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_undefined(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_true(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_true(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_false(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_false(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_exception(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_exception(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_uninitialized(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_uninitialized(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_bool(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Bool
    bool value = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_new_bool(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_int32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Int32
    std::int32_t value = gm::wire::codec::readValue<std::int32_t>(__br);

    auto&& __result = iqjs_new_int32(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_int64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Int64
    std::int64_t value = gm::wire::codec::readValue<std::int64_t>(__br);

    auto&& __result = iqjs_new_int64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_uint32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt32
    std::uint32_t value = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = iqjs_new_uint32(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_uint64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_uint64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_float64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Float32
    float value = gm::wire::codec::readValue<float>(__br);

    auto&& __result = iqjs_new_float64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_number(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Float32
    float value = gm::wire::codec::readValue<float>(__br);

    auto&& __result = iqjs_new_number(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_bigint64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Int64
    std::int64_t value = gm::wire::codec::readValue<std::int64_t>(__br);

    auto&& __result = iqjs_new_bigint64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_biguint64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_biguint64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_catch_offset(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: Int32
    std::int32_t value = gm::wire::codec::readValue<std::int32_t>(__br);

    auto&& __result = iqjs_new_catch_offset(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_string(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_string(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_string_len(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    // field: byte_count, type: UInt64
    std::uint64_t byte_count = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_string_len(ctx, value, byte_count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_string_utf16(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: code_units, type: UInt16[]
    std::vector<std::uint16_t> code_units = gm::wire::codec::readVector<std::uint16_t>(__br);

    auto&& __result = iqjs_new_string_utf16(ctx, code_units);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_atom_string(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: String
    std::string_view value = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_atom_string(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_symbol(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: description, type: String
    std::string_view description = gm::wire::codec::readValue<std::string_view>(__br);

    // field: is_global, type: Bool
    bool is_global = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_new_symbol(ctx, description, is_global);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_value(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_value(ctx, value);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_free_value_rt(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_free_value_rt(rt, value);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_dup_value(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_dup_value(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_dup_value_rt(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_dup_value_rt(rt, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_value_tag(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_value_tag(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_nan(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_nan(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_number(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_number(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_bigint(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_bigint(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_bool(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_bool(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_null(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_null(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_undefined(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_undefined(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_exception(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_exception(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_uninitialized(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_uninitialized(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_string(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_string(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_symbol(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_symbol(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_object(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_object(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_module(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_module(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_error(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_error(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_uncatchable_error(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_uncatchable_error(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_uncatchable_error(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_uncatchable_error(ctx, value);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_clear_uncatchable_error(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_clear_uncatchable_error(ctx, value);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_reset_uncatchable_error(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_reset_uncatchable_error(ctx);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_throw(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_exception(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_exception(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_has_exception(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_has_exception(ctx);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_new_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_error(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_internal_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_internal_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_plain_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_plain_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_range_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_range_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_reference_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_reference_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_syntax_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_syntax_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_type_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_new_type_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_internal_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_internal_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_plain_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_plain_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_range_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_range_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_reference_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_reference_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_syntax_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_syntax_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_type_error(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_type_error(ctx, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_dom_exception(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: message, type: String
    std::string_view message = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_throw_dom_exception(ctx, name, message);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_throw_out_of_memory(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_throw_out_of_memory(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_equal(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: left, type: UInt64
    std::uint64_t left = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: right, type: UInt64
    std::uint64_t right = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_equal(ctx, left, right);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_strict_equal(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: left, type: UInt64
    std::uint64_t left = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: right, type: UInt64
    std::uint64_t right = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_strict_equal(ctx, left, right);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_same_value(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: left, type: UInt64
    std::uint64_t left = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: right, type: UInt64
    std::uint64_t right = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_same_value(ctx, left, right);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_same_value_zero(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: left, type: UInt64
    std::uint64_t left = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: right, type: UInt64
    std::uint64_t right = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_same_value_zero(ctx, left, right);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_to_bool(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_bool(ctx, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_to_boolean(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_boolean(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_number(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_number(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_int32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_int32(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSInt32Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_uint32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_uint32(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSUInt32Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_int64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_int64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_index(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_index(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSUInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_float64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_float64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSFloatResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_bigint64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_bigint64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_biguint64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_biguint64(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSUInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_int64_ext(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_int64_ext(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_string(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_string(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_property_key(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_property_key(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT char* __EXT_NATIVE__iqjs_to_cstring(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: cesu8, type: Bool
    bool cesu8 = gm::wire::codec::readValue<bool>(__br);

    static std::string __result;
    __result = iqjs_to_cstring(ctx, value, cesu8);
    return (char*)__result.c_str();
}

GMEXPORT double __EXT_NATIVE__iqjs_to_utf16(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_utf16(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt16[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object_proto(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proto, type: UInt64
    std::uint64_t proto = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object_proto(ctx, proto);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object_class(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object_class(ctx, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object_proto_class(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proto, type: UInt64
    std::uint64_t proto = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object_proto_class(ctx, proto, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object_from(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atoms, type: UInt64[]
    std::vector<std::uint64_t> atoms = gm::wire::codec::readVector<std::uint64_t>(__br);

    // field: values, type: UInt64[]
    std::vector<std::uint64_t> values = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object_from(ctx, atoms, values);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_object_from_str(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: names, type: String[]
    std::vector<std::string_view> names = gm::wire::codec::readVector<std::string_view>(__br);

    // field: values, type: UInt64[]
    std::vector<std::uint64_t> values = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_new_object_from_str(ctx, names, values);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_object(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_object(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_to_object_string(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_to_object_string(ctx, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_array(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_array(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_array_from(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: values, type: UInt64[]
    std::vector<std::uint64_t> values = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_new_array_from(ctx, values);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_date(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: epoch_ms, type: Float32
    float epoch_ms = gm::wire::codec::readValue<float>(__br);

    auto&& __result = iqjs_new_date(ctx, epoch_ms);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_proxy(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: target, type: UInt64
    std::uint64_t target = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: handler, type: UInt64
    std::uint64_t handler = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_proxy(ctx, target, handler);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_proxy_target(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proxy, type: UInt64
    std::uint64_t proxy = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_proxy_target(ctx, proxy);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_proxy_handler(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proxy, type: UInt64
    std::uint64_t proxy = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_proxy_handler(ctx, proxy);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_function(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_function(ctx, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_async_function(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_async_function(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_constructor(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_constructor(ctx, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_constructor_bit(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: enabled, type: Bool
    bool enabled = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_set_constructor_bit(ctx, value, enabled);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_regexp(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_regexp(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_map(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_map(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_set(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_set(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_weak_ref(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_weak_ref(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_weak_set(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_weak_set(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_weak_map(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_weak_map(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_data_view(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_data_view(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_array(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_array(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_proxy(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_proxy(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_date(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_date(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_property(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_property(ctx, object, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_property_uint32(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: index, type: UInt32
    std::uint32_t index = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = iqjs_get_property_uint32(ctx, object, index);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_property_int64(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: index, type: Int64
    std::int64_t index = gm::wire::codec::readValue<std::int64_t>(__br);

    auto&& __result = iqjs_get_property_int64(ctx, object, index);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_property_str(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_get_property_str(ctx, object, name);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_property(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_property(ctx, object, atom, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_property_uint32(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: index, type: UInt32
    std::uint32_t index = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_property_uint32(ctx, object, index, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_property_int64(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: index, type: Int64
    std::int64_t index = gm::wire::codec::readValue<std::int64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_property_int64(ctx, object, index, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_property_str(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_property_str(ctx, object, name, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_has_property(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_has_property(ctx, object, atom);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_extensible(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_extensible(ctx, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_prevent_extensions(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_prevent_extensions(ctx, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_delete_property(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_delete_property(ctx, object, atom, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_prototype(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proto, type: UInt64
    std::uint64_t proto = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_prototype(ctx, object, proto);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_prototype(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_prototype(ctx, object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_length(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_length(ctx, object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSInt64Result
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_length(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: new_length, type: Int64
    std::int64_t new_length = gm::wire::codec::readValue<std::int64_t>(__br);

    auto&& __result = iqjs_set_length(ctx, object, new_length);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_seal_object(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_seal_object(ctx, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_freeze_object(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_freeze_object(ctx, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_own_property_names(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSGPNFlags
    gm_enums::IQJSGPNFlags flags = gm::wire::codec::readValue<gm_enums::IQJSGPNFlags>(__br);

    auto&& __result = iqjs_get_own_property_names(ctx, object, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSPropertyEnumEntry[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_own_property(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_own_property(ctx, object, atom);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSPropertyDescriptorResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_define_property(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: getter, type: UInt64
    std::uint64_t getter = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: setter, type: UInt64
    std::uint64_t setter = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_define_property(ctx, object, atom, value, getter, setter, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_define_property_value(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_define_property_value(ctx, object, atom, value, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_define_property_value_uint32(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: index, type: UInt32
    std::uint32_t index = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_define_property_value_uint32(ctx, object, index, value, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_define_property_value_str(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_define_property_value_str(ctx, object, name, value, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_define_property_get_set(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: getter, type: UInt64
    std::uint64_t getter = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: setter, type: UInt64
    std::uint64_t setter = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSPropertyFlags
    gm_enums::IQJSPropertyFlags flags = gm::wire::codec::readValue<gm_enums::IQJSPropertyFlags>(__br);

    auto&& __result = iqjs_define_property_get_set(ctx, object, atom, getter, setter, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_constructor(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: proto, type: UInt64
    std::uint64_t proto = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_constructor(ctx, function_value, proto);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_instance_of(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_instance_of(ctx, value, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_is_html_dda(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_set_is_html_dda(ctx, object);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_set_opaque(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: pointer, type: UInt64
    std::uint64_t pointer = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_set_opaque(object, pointer);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_get_opaque(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_get_opaque(object, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_get_opaque2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: class_id, type: UInt64
    std::uint64_t class_id = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_get_opaque2(ctx, object, class_id);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_get_any_opaque(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_get_any_opaque(object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSOpaqueResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_detect_module(char* source)
{
    auto&& __result = iqjs_detect_module(source);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_eval(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    // field: filename, type: String
    std::string_view filename = gm::wire::codec::readValue<std::string_view>(__br);

    // field: flags, type: enum IQJSEvalFlags
    gm_enums::IQJSEvalFlags flags = gm::wire::codec::readValue<gm_enums::IQJSEvalFlags>(__br);

    auto&& __result = iqjs_eval(ctx, source, filename, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_eval2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    // field: options, type: struct IQJSEvalOptions
    gm_structs::IQJSEvalOptions options = gm::wire::codec::readValue<gm_structs::IQJSEvalOptions>(__br);

    auto&& __result = iqjs_eval2(ctx, source, options);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_eval_this(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: this_value, type: UInt64
    std::uint64_t this_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    // field: filename, type: String
    std::string_view filename = gm::wire::codec::readValue<std::string_view>(__br);

    // field: flags, type: enum IQJSEvalFlags
    gm_enums::IQJSEvalFlags flags = gm::wire::codec::readValue<gm_enums::IQJSEvalFlags>(__br);

    auto&& __result = iqjs_eval_this(ctx, this_value, source, filename, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_eval_this2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: this_value, type: UInt64
    std::uint64_t this_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    // field: options, type: struct IQJSEvalOptions
    gm_structs::IQJSEvalOptions options = gm::wire::codec::readValue<gm_structs::IQJSEvalOptions>(__br);

    auto&& __result = iqjs_eval_this2(ctx, this_value, source, options);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_eval_function(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_eval_function(ctx, function_value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_global_object(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_global_object(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_parse_json(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: json, type: String
    std::string_view json = gm::wire::codec::readValue<std::string_view>(__br);

    // field: filename, type: String
    std::string_view filename = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_parse_json(ctx, json, filename);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_json_stringify(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: replacer, type: UInt64
    std::uint64_t replacer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: space, type: UInt64
    std::uint64_t space = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_json_stringify(ctx, object, replacer, space);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_array_buffer_copy(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = iqjs_new_array_buffer_copy(ctx, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_array_buffer_owned(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    // field: is_shared, type: Bool
    bool is_shared = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_new_array_buffer_owned(ctx, data, is_shared);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_detach_array_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_detach_array_buffer(ctx, object);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_copy_array_buffer(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destination, type: Buffer
    gm::wire::GMBuffer destination = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = iqjs_copy_array_buffer(ctx, object, destination);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: Int64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_array_buffer_copy(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_array_buffer_copy(ctx, object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt8[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_array_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_array_buffer(object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_is_immutable_array_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_immutable_array_buffer(object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_immutable_array_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: immutable, type: Bool
    bool immutable = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_set_immutable_array_buffer(object, immutable);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_uint8_array_copy(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_uint8_array_copy(ctx, object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt8[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_typed_array(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    // field: array_type, type: enum IQJSTypedArrayType
    gm_enums::IQJSTypedArrayType array_type = gm::wire::codec::readValue<gm_enums::IQJSTypedArrayType>(__br);

    auto&& __result = iqjs_new_typed_array(ctx, arguments, array_type);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_typed_array_buffer(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_typed_array_buffer(ctx, object);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSTypedArrayBufferInfo
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_uint8_array_copy(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = iqjs_new_uint8_array_copy(ctx, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_uint8_array_owned(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    // field: is_shared, type: Bool
    bool is_shared = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = iqjs_new_uint8_array_owned(ctx, data, is_shared);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_typed_array_type(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_typed_array_type(object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_set_shared_array_buffer_policy(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: policy, type: String
    std::string_view policy = gm::wire::codec::readValue<std::string_view>(__br);

    // field: opaque, type: UInt64
    std::uint64_t opaque = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_unsafe_set_shared_array_buffer_policy(rt, policy, opaque);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_promise_capability(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_promise_capability(ctx);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSPromiseCapability
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_promise_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: promise, type: UInt64
    std::uint64_t promise = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_promise_state(ctx, promise);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: enum IQJSPromiseState
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_promise_result(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: promise, type: UInt64
    std::uint64_t promise = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_promise_result(ctx, promise);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_is_promise(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_is_promise(value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_new_settled_promise(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: is_reject, type: Bool
    bool is_reject = gm::wire::codec::readValue<bool>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_new_settled_promise(ctx, is_reject, value);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_create(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_module_registry_create(rt);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_add(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registry, type: UInt64
    std::uint64_t registry = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    iqjs_module_registry_add(registry, name, source);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_remove(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registry, type: UInt64
    std::uint64_t registry = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    iqjs_module_registry_remove(registry, name);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_set_supported_attributes(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registry, type: UInt64
    std::uint64_t registry = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: attributes, type: String[]
    std::vector<std::string_view> attributes = gm::wire::codec::readVector<std::string_view>(__br);

    iqjs_module_registry_set_supported_attributes(registry, attributes);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_install(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: registry, type: UInt64
    std::uint64_t registry = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: attributes_aware, type: Bool
    bool attributes_aware = gm::wire::codec::readValue<bool>(__br);

    iqjs_module_registry_install(rt, registry, attributes_aware);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_module_registry_free(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registry, type: UInt64
    std::uint64_t registry = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_module_registry_free(registry);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_import_meta(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_import_meta(ctx, module_handle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_module_name(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_module_name(ctx, module_handle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_get_module_namespace(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_module_namespace(ctx, module_handle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_module_private_value(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_module_private_value(ctx, module_handle, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_module_private_value(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_get_module_private_value(ctx, module_handle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_load_module(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: basename, type: String
    std::string_view basename = gm::wire::codec::readValue<std::string_view>(__br);

    // field: filename, type: String
    std::string_view filename = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_load_module(ctx, basename, filename);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_resolve_module(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_resolve_module(ctx, object);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_get_script_or_module_name(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: levels, type: Int32
    std::int32_t levels = gm::wire::codec::readValue<std::int32_t>(__br);

    auto&& __result = iqjs_get_script_or_module_name(ctx, levels);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_c_module_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: export_names, type: String[]
    std::vector<std::string_view> export_names = gm::wire::codec::readVector<std::string_view>(__br);

    auto&& __result = iqjs_new_c_module_adapter(ctx, name, export_names);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_add_module_export(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = iqjs_add_module_export(ctx, module_handle, name);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_module_export(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: value, type: UInt64
    std::uint64_t value = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = iqjs_set_module_export(ctx, module_handle, name, value);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_property_function_list_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: entries, type: struct IQJSFunctionListEntry[]
    std::vector<gm_structs::IQJSFunctionListEntry> entries = gm::wire::codec::readVector<gm_structs::IQJSFunctionListEntry>(__br);

    auto&& __result = iqjs_set_property_function_list_adapter(ctx, object, entries);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_add_module_export_list_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: entries, type: struct IQJSFunctionListEntry[]
    std::vector<gm_structs::IQJSFunctionListEntry> entries = gm::wire::codec::readVector<gm_structs::IQJSFunctionListEntry>(__br);

    auto&& __result = iqjs_add_module_export_list_adapter(ctx, module_handle, entries);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_set_module_export_list_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: module_handle, type: UInt64
    std::uint64_t module_handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: entries, type: struct IQJSFunctionListEntry[]
    std::vector<gm_structs::IQJSFunctionListEntry> entries = gm::wire::codec::readVector<gm_structs::IQJSFunctionListEntry>(__br);

    auto&& __result = iqjs_set_module_export_list_adapter(ctx, module_handle, entries);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_write_object(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSWriteObjectFlags
    gm_enums::IQJSWriteObjectFlags flags = gm::wire::codec::readValue<gm_enums::IQJSWriteObjectFlags>(__br);

    auto&& __result = iqjs_write_object(ctx, object, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt8[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_write_object2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: object, type: UInt64
    std::uint64_t object = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: enum IQJSWriteObjectFlags
    gm_enums::IQJSWriteObjectFlags flags = gm::wire::codec::readValue<gm_enums::IQJSWriteObjectFlags>(__br);

    auto&& __result = iqjs_unsafe_write_object2(ctx, object, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct IQJSSerializedObject
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_read_object(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    // field: flags, type: enum IQJSReadObjectFlags
    gm_enums::IQJSReadObjectFlags flags = gm::wire::codec::readValue<gm_enums::IQJSReadObjectFlags>(__br);

    auto&& __result = iqjs_read_object(ctx, data, flags);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_unsafe_read_object2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    // field: flags, type: enum IQJSReadObjectFlags
    gm_enums::IQJSReadObjectFlags flags = gm::wire::codec::readValue<gm_enums::IQJSReadObjectFlags>(__br);

    // field: shared_array_buffer_pointers, type: UInt64[]
    std::vector<std::uint64_t> shared_array_buffer_pointers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_unsafe_read_object2(ctx, data, flags, shared_array_buffer_pointers);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_interrupt_handler_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_set_interrupt_handler_adapter(rt, callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_host_promise_rejection_tracker_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_set_host_promise_rejection_tracker_adapter(rt, callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_set_promise_hook_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: rt, type: UInt64
    std::uint64_t rt = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_set_promise_hook_adapter(rt, callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_remove_callback_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: registration, type: UInt64
    std::uint64_t registration = gm::wire::codec::readValue<std::uint64_t>(__br);

    iqjs_remove_callback_adapter(registration);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_gml_function_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: function_length, type: Int32
    std::int32_t function_length = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: magic, type: Int32
    std::int32_t magic = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_new_gml_function_adapter(ctx, name, function_length, magic, callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_gml_function_data_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: function_length, type: Int32
    std::int32_t function_length = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: magic, type: Int32
    std::int32_t magic = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: data, type: UInt64[]
    std::vector<std::uint64_t> data = gm::wire::codec::readVector<std::uint64_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_new_gml_function_data_adapter(ctx, name, function_length, magic, data, callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_new_gml_closure_adapter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: function_length, type: Int32
    std::int32_t function_length = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: magic, type: Int32
    std::int32_t magic = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    // field: finalize_callback, type: Function
    gm::wire::GMFunction finalize_callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_new_gml_closure_adapter(ctx, name, function_length, magic, callback, finalize_callback);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_register_gml_global_function(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    // field: callback, type: Function
    gm::wire::GMFunction callback = gm::wire::codec::readFunction(__br, &__dispatch_queue);

    auto&& __result = iqjs_register_gml_global_function(ctx, name, callback);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_unregister_gml_global_function(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    iqjs_unregister_gml_global_function(ctx, name);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_enqueue_job_adapter(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_enqueue_job_adapter(ctx, function_value, arguments);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__iqjs_call(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: this_value, type: UInt64
    std::uint64_t this_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_call(ctx, function_value, this_value, arguments);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_invoke(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: this_value, type: UInt64
    std::uint64_t this_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: atom, type: UInt64
    std::uint64_t atom = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_invoke(ctx, this_value, atom, arguments);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_call_constructor(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_call_constructor(ctx, function_value, arguments);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__iqjs_call_constructor2(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: ctx, type: UInt64
    std::uint64_t ctx = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: function_value, type: UInt64
    std::uint64_t function_value = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: new_target, type: UInt64
    std::uint64_t new_target = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: arguments, type: UInt64[]
    std::vector<std::uint64_t> arguments = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = iqjs_call_constructor2(ctx, function_value, new_target, arguments);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

