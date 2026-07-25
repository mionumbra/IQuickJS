#include "iqjs_handles.h"
#include "quickjs.h"

#ifdef _MSC_VER
#pragma warning(disable : 4576)
#endif

namespace iqjs {

// =============================================================================
// Trampoline invoked by QuickJS when a registered GML function is called
// from JS code. Dispatches the call asynchronously to the next GML frame via
// the GMFunction/DispatchQueue infrastructure.
// =============================================================================
JSValue gml_trampoline(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv,
                       int /*magic*/, JSValueConst* func_data)
{
    std::int64_t raw_id = 0;
    if (JS_ToInt64(ctx, &raw_id, func_data[0]) < 0 || raw_id <= 0)
        return JS_ThrowTypeError(ctx, "invalid GML callback registration");
    const Handle reg_id = static_cast<Handle>(raw_id);

    RegEntry entry;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        auto it = gml_funcs().find(reg_id);
        if (it == gml_funcs().end()) {
            return JS_ThrowTypeError(ctx, "GML callback registration has been removed");
        }
        entry = it->second;
    }

    if (!entry.callback) {
        return JS_ThrowTypeError(ctx, "GML callback is not callable");
    }

    // Build the argument list. Each argument is wrapped as a uint64 value
    // handle (with its own refcount) so the GML function can call any other
    // IQuickJS function on it (e.g. to inspect type or call methods).
    std::vector<std::uint64_t> arg_handles;
    arg_handles.reserve(static_cast<size_t>(argc));
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        arg_handles.push_back(value_to_handle(JS_DupValue(ctx, this_val), ctx));
        for (int i = 0; i < argc; ++i) {
            JSValue dup = JS_DupValue(ctx, argv[i]);
            arg_handles.push_back(value_to_handle(dup, ctx));
        }
    }

    // Queue the call onto the GML dispatch queue.
    gm::wire::ArrayStream args;
    args.push(entry.magic);
    for (auto h : arg_handles) args.push(h);
    for (auto h : entry.data) args.push(h);
    entry.callback.call_with_args(args);

    return JS_UNDEFINED;
}

// =============================================================================
// Interrupt handler invoked by QuickJS on the runtime thread. Forwards to
// the registered GML callback (if any). The return value tells QuickJS
// whether to interrupt execution; we forward whatever the GML side returns
// (mapped to 0/1 by a side-channel write).
// =============================================================================
int qjs_interrupt_handler(JSRuntime* rt, void* /*opaque*/)
{
    gm::wire::GMFunction callback;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        auto it = host_callbacks().find(rt);
        if (it == host_callbacks().end() || !it->second.interrupt) {
            return 0;
        }
        auto entry = callback_entries().find(it->second.interrupt);
        if (entry == callback_entries().end()) return 0;
        callback = entry->second.callback;
    }

    // GMFunction dispatch is asynchronous and cannot provide QuickJS' required
    // synchronous decision. Registration rejects this path, so this is a guard.
    if (callback) callback.call();
    return 1;
}

// =============================================================================
// Host promise rejection tracker
// =============================================================================
void qjs_promise_rejection_tracker(JSContext* ctx, JSValueConst promise, JSValueConst reason, bool is_handled, void* /*opaque*/)
{
    JSRuntime* rt = JS_GetRuntime(ctx);

    gm::wire::GMFunction callback;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        auto it = host_callbacks().find(rt);
        if (it == host_callbacks().end() || !it->second.rejection_tracker) {
            return;
        }
        auto entry = callback_entries().find(it->second.rejection_tracker);
        if (entry == callback_entries().end()) return;
        callback = entry->second.callback;
    }

    std::uint64_t promise_h = 0;
    std::uint64_t reason_h = 0;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        promise_h = value_to_handle(JS_DupValue(ctx, promise), ctx);
        reason_h  = value_to_handle(JS_DupValue(ctx, reason), ctx);
    }

    gm::wire::ArrayStream args;
    args.push(promise_h);
    args.push(reason_h);
    args.push(static_cast<bool>(is_handled));
    callback.call_with_args(args);
}

void qjs_promise_hook(JSContext* ctx, JSPromiseHookType type, JSValueConst promise,
                      JSValueConst parent, void* /*opaque*/)
{
    gm::wire::GMFunction callback;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        auto hosts = host_callbacks().find(JS_GetRuntime(ctx));
        if (hosts == host_callbacks().end() || !hosts->second.promise_hook) return;
        auto entry = callback_entries().find(hosts->second.promise_hook);
        if (entry == callback_entries().end()) return;
        callback = entry->second.callback;
    }
    Handle promise_h = 0;
    Handle parent_h = 0;
    {
        std::lock_guard<TableMutex> lk(table_mutex());
        promise_h = value_to_handle(JS_DupValue(ctx, promise), ctx);
        parent_h = value_to_handle(JS_DupValue(ctx, parent), ctx);
    }
    gm::wire::ArrayStream args;
    args.push(static_cast<std::int32_t>(type));
    args.push(promise_h);
    args.push(parent_h);
    callback.call_with_args(args);
}

} // namespace iqjs
