# IQuickJS quickjs-ng API design

## Scope

IQuickJS is a general-purpose GameMaker extension for embedding QuickJS-NG.
It targets the public API in `third_party/quickjs-ng/quickjs.h`, not a single
application or data format. The header currently exports 260 functions with
`JS_EXTERN`; inline constructors and predicates are exposed as regular
IQuickJS functions where useful.

The extension owns runtime, context, value, atom, module, buffer, promise,
object, evaluation, serialization, and callback adapters. Application-specific
protocols should be implemented in JavaScript or in a separate optional native
adapter, rather than added to the core GMIDL surface.

## ABI mapping

| QuickJS C type | GML representation |
| --- | --- |
| `JSRuntime *` | `uint64` runtime handle |
| `JSContext *` | `uint64` context handle |
| `JSValue` | `uint64` owned value handle |
| `JSAtom` | `uint64` owned atom handle |
| `JSClassID` | `uint64` class-id handle |
| `JSModuleDef *` | `uint64` borrowed module handle |
| `void *` | `uint64` pointer handle; never dereferenced by GML |
| `size_t *`, numeric out parameters | typed result struct |
| returned byte pointer | copied `uint8[]` or caller-provided GM buffer |
| C callback/function table | native registration object backed by `GMFunction` |

## Ownership

- New values returned by QuickJS become owned value handles.
- APIs documented by QuickJS as consuming a `JSValue` consume the handle.
- `iqjs_value_dup` creates a second owned handle.
- Freeing a context invalidates all values and atoms belonging to that context.
- Freeing a runtime first frees all contexts and registrations owned by it.
- Constants such as null and undefined are represented by normal handles, not
  magic numeric values shared across contexts.

## Callback boundary

QuickJS callbacks are synchronous C callbacks; `GMFunction` dispatch is
asynchronous. Therefore callback APIs use one of two adapters:

1. Notification callbacks queue a `GMFunction` call and return the documented
   neutral value immediately.
2. Synchronous host functions are implemented as native collectors or as
   promise-returning functions. They do not block the GameMaker runner while
   waiting for the next frame.

The optional beatmap example uses a native synchronous collector because its API
depends on chaining (`withProperty(...).p(...)`) and immediate mutation.

## Optional Beatmap Example

`project/datafiles/_Drizzle_雨之城 - CsLrisEto.js` requires:

- classic global script evaluation;
- `let`, `for`, functions and chained calls;
- a synchronous global `MilizeBeatmap` object with `timing`, `note`,
  `animation`, `withProperty`, and `line` members;
- deterministic JSON extraction after evaluation.

Node-specific code in `conv - 副本.js` (`require`, `process`, `fs`) is a
development converter and is not executed by the embedded runtime.

## Validation

1. Build `IQuickJS.dll` with VS 18 / v145.
2. Run the generic native smoke test for runtime, context, evaluation, and
   value conversion.
3. Use `gm-cli compile project/IQuickJS.yyp --target=windows --runtime=vm`.
4. Run the GameMaker project and verify the generic evaluation smoke test.

## Regeneration

`extgen v1.0.1` rewrites the root `CMakeLists.txt` and `CMakePresets.json`.
After regeneration, restore the project-owned C language declaration and the
selected Visual Studio generator/toolset before configuring a build. Do not
run generation concurrently with CMake configuration or compilation.
