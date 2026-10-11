# Lox Interpreter

A C++17 tree-walking interpreter for Lox, following *Crafting Interpreters*.

### Build

This project uses Bazel (version pinned in `.bazelversion`). Install [bazelisk](https://github.com/bazelbuild/bazelisk) (`brew install bazelisk`) to get the right version automatically.

To build the interpreter:
```
bazel build //src:lox
```

The binary is located at `bazel-bin/src/lox`

To run tests:
```
bazel test //test/...
bazel test --config=asan //test/...   # with AddressSanitizer + UBSan
```

### Tooling

- `bazel run //:refresh_compile_commands` generates `compile_commands.json` for clangd/IDEs.
- `clang-format -i src/*.?pp test/*.cpp` formats code (`.clang-format`); `.clang-tidy` configures lint checks.
