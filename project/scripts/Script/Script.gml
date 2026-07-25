function iqjs_runner_smoke_test()
{
    var _runtime = iqjs_new_runtime();
    if (_runtime == 0) {
        show_error("IQUICKJS_SMOKE_FAIL: cannot create QuickJS runtime", true);
        return;
    }

    var _context = iqjs_new_context(_runtime);
    if (_context == 0) {
        iqjs_free_runtime(_runtime);
        show_error("IQUICKJS_SMOKE_FAIL: cannot create QuickJS context", true);
        return;
    }

    var _value = iqjs_eval(_context, "JSON.stringify({ok: true, value: 42})", "smoke.js", IQJSEvalFlags.Global);
    var _json = iqjs_to_cstring(_context, _value, false);
    var _passed = (_json == "{\"ok\":true,\"value\":42}");

    iqjs_free_value(_context, _value);
    iqjs_free_context(_context);
    iqjs_free_runtime(_runtime);

    if (!_passed) {
        show_error("IQUICKJS_SMOKE_FAIL: result=" + _json, true);
        return;
    }

    show_debug_message("IQUICKJS_SMOKE_PASS result=" + _json);
}
