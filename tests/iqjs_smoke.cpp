#include "native/IQuickJSInternal_native.h"
#include "native/iqjs_handles.h"
#include "quickjs.h"

#include <iostream>
#include <string>

int main()
{
    iqjs_init();
    const std::uint64_t runtime = iqjs_new_runtime();
    const std::uint64_t context = iqjs_new_context(runtime);
    const std::uint64_t duplicate_context = iqjs_dup_context(context);
    const std::uint64_t second_context = iqjs_new_context(runtime);
    if (!runtime || !context || !duplicate_context || !second_context) {
        std::cerr << "cannot create QuickJS runtime/context\n";
        return 3;
    }

    const std::uint64_t value = iqjs_eval(context, "JSON.stringify({ok: true, value: 42})", "smoke.js", gm_enums::IQJSEvalFlags::Global);
    const std::string result = iqjs_to_cstring(context, value, false);
    const bool same_context_ok = iqjs_to_cstring(duplicate_context, value, false) == result;
    const bool foreign_context_rejected = iqjs_to_cstring(second_context, value, false).empty();
    iqjs_free_context(duplicate_context);
    const bool duplicate_release_keeps_context_alive = iqjs_to_cstring(context, value, false) == result;
    const bool ok = result == "{\"ok\":true,\"value\":42}" && same_context_ok &&
        foreign_context_rejected && duplicate_release_keeps_context_alive;
    if (!ok) std::cerr << "unexpected eval result: " << result << '\n';
    iqjs_free_value(context, value);

    iqjs_free_context(second_context);
    iqjs_free_context(context);
    iqjs_free_runtime(runtime);
    iqjs_shutdown();

    if (!ok) return 1;
    std::cout << "generic QuickJS smoke test passed\n";
    return 0;
}
