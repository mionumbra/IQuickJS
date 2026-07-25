# IQuickJS

IQuickJS is a GameMaker native extension that embeds [QuickJS-NG](https://github.com/quickjs-ng/quickjs). It exposes runtime, context, value, atom, module, object, evaluation, buffer, promise, serialization, and callback APIs through generated GML bindings.

The extension targets QuickJS-NG 0.15.1 and uses opaque `uint64` handles for native QuickJS resources. The generated API surface is defined in [`api.gmidl`](api.gmidl); ownership and ABI details are documented in [`docs/quickjs-ng-api-design.md`](docs/quickjs-ng-api-design.md).

## Requirements

- Git with submodule support
- CMake 3.21 or newer
- A C++20 toolchain
- [GM-ExtensionGenerator](https://github.com/YoYoGames/GM-ExtensionGenerator) `v1.0.1` to regenerate bindings
- GameMaker and `gm-cli` to compile the sample GameMaker project

Windows release builds use the Visual Studio generator and toolset declared in `CMakePresets.json`. Other platform presets require their respective platform SDKs and toolchains.

## Clone

```powershell
git clone --recurse-submodules https://github.com/mionumbra/IQuickJS.git
Set-Location IQuickJS
```

For an existing clone:

```powershell
git submodule update --init --recursive
```

## Build

Configure and build the Windows release extension:

```powershell
cmake --preset win-x64-release
cmake --build --preset win-x64-release --config Release
```

The resulting DLL is copied to `project/extensions/IQuickJS/` by the preset. See `CMakePresets.json` for other available platform configurations. Console presets require the corresponding proprietary SDKs and are not available in public CI.

## Test

The native smoke test validates runtime creation, context creation, evaluation, and value conversion without requiring GameMaker:

```powershell
cmake -S tests -B out/smoke
cmake --build out/smoke --config Release
ctest --test-dir out/smoke -C Release --output-on-failure
```

To validate the GameMaker project after building the extension:

```powershell
gm-cli compile project/IQuickJS.yyp --target=windows --runtime=vm
```

## Regenerate Bindings

`extgen` owns `CMakeLists.txt`, `CMakePresets.json`, `code_gen/`, generated GML wrappers, injectors, extension declarations, and generated API documentation. Use the version documented above:

```powershell
extgen --config config.json
```

Review every generated change before committing. The project keeps generated CMake and binding sources under version control so a fresh clone can build and run the smoke test. Do not place custom native implementation in `code_gen/`; use `src/` instead.

## Safety And Ownership

Release every runtime, context, value, atom, buffer, module, and registration handle with its corresponding API when it is no longer needed. Freeing a context invalidates resources that belong to it; freeing a runtime also frees its contexts.

Functions prefixed `iqjs_unsafe_` accept or expose native pointer values. Invalid, stale, cross-runtime, or incorrectly sized pointers can crash or corrupt the process. Do not use these APIs with values not created and controlled by compatible native code.

## License

This repository does not yet declare a license for IQuickJS itself. The QuickJS-NG dependency is provided as a Git submodule and retains its own MIT license in `third_party/quickjs-ng/LICENSE`.

## Contributing

Read [`CONTRIBUTING.md`](CONTRIBUTING.md) before opening a change. Please report vulnerabilities through [`SECURITY.md`](SECURITY.md), not public issues.
