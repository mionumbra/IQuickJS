# Contributing

## Development Setup

Clone the repository with its submodules:

```powershell
git clone --recurse-submodules https://github.com/mionumbra/IQuickJS.git
Set-Location IQuickJS
```

Use `extgen v1.0.1` when regenerating bindings. The generated files are committed so contributors can build from a clean clone; custom native implementation belongs in `src/`, never `code_gen/`.

## Before Opening A Pull Request

1. Initialize submodules with `git submodule update --init --recursive`.
2. Run the native smoke test:

```powershell
cmake -S tests -B out/smoke
cmake --build out/smoke --config Release
ctest --test-dir out/smoke -C Release --output-on-failure
```

3. If you changed `api.gmidl` or `config.json`, regenerate with `extgen --config config.json` and include all intended generated changes.
4. If you changed the GameMaker-facing API, compile `project/IQuickJS.yyp` with `gm-cli` where available.

## Change Scope

- Keep public API and generated binding changes together.
- Document ownership changes for native handles in `docs/quickjs-ng-api-design.md`.
- Do not commit binaries, CMake build directories, test logs, or local preset overrides.
- Do not update the QuickJS-NG submodule incidentally. Explain dependency updates and test them explicitly.
