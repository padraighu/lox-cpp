# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

A C++17 tree-walking interpreter for Lox, following *Crafting Interpreters* (jlox, ported to C++). Currently implements expressions only (scanning, parsing, evaluating); statements such as `print`/`var`/`if` in `src/hello.lox` are not yet supported.

## Commands

Bazel via bazelisk; the version is pinned in `.bazelversion` (Bazel 9, Bzlmod deps in `MODULE.bazel`). `.bazelrc` sets C++17 and `-Wall -Wextra -Wpedantic`, with `-Werror` applied to `src/` and `test/` only, so new warnings fail the build.

```sh
bazel build //src:lox                      # binary at bazel-bin/src/lox
bazel-bin/src/lox                          # REPL
bazel-bin/src/lox path/to/file.lox         # run a script (exit 65 = compile error, 70 = runtime error)

bazel test //test/...                      # all tests
bazel test --config=asan //test/...        # with ASan + UBSan
bazel test --test_output=all //test:parser_test   # one test target
bazel test //test:parser_test --test_arg=--gtest_filter='ParserTest.*'  # one gtest case

bazel run //:refresh_compile_commands      # regenerate compile_commands.json for clangd
clang-format -i src/*.?pp test/*.cpp       # format (.clang-format)
```

Test targets (`scanner_test`, `parser_test`, `astprinter_test`, `interpreter_test`) are GoogleTest binaries generated from a name list in `test/BUILD`; a new `test/foo_test.cpp` just needs its name added there. BUILD files must `load()` cc rules from `@rules_cc` (Bazel 9 has no native cc rules). `hedron_compile_commands` is unmaintained and only works via the `--incompatible_autoload_externally` line in `.bazelrc`.

## Architecture

Pipeline in `Lox::run` (`src/lox.cpp`): `Scanner` → tokens → `Parser` (recursive descent) → `std::shared_ptr<Expr>` AST → `Interpreter` (visitor) evaluates and prints the result.

- **Library vs. binary**: `cc_library lox-library` globs `src/*.cpp`/`*.hpp` (excluding `main.cpp`), so new source files are picked up automatically without editing `src/BUILD`. Tests link the library and typically drive `Lox::run` directly.
- **AST is generated**: `src/expr.hpp` and `src/expr.cpp` are produced by `tool/generate_ast.py` (run from repo root: `python3 tool/generate_ast.py`; it clang-formats its output). To add an expression node, edit the `types` list there and regenerate rather than hand-editing, then implement the new `visit*Expr` method in every `Visitor` subclass (`Interpreter`, `AstPrinter`).
- **Visitor returns `std::any`**: visitors return `std::any`; the interpreter stores runtime values as `LiteralValue` and unwraps with `std::any_cast<LiteralValue>`.
- **Values**: `LiteralValue` (`src/literal.hpp`) is the single value type for both token literals and runtime values — wrapping `std::variant<std::monostate, bool, double, std::string>` (monostate = `nil`). Construct via the `make*Literal` factories; `get*Value` throws `bad_variant_access` on the wrong type, so check `is*` first. `operator==` implements Lox equality and `toString()` is the canonical printed form (numbers use the shortest round-trip digits).
- **Errors**: a shared `ErrorReporter` instance is passed (as `shared_ptr`) into `Lox`, `Scanner`, `Parser`, and `Interpreter`; it records `hadError` / `hadRuntimeError`. The parser throws `ParseError` internally and catches it in `Parser::parse()` (returning null); the interpreter throws `RuntimeError` and catches it in `Interpreter::interpret()`, reporting via `ErrorReporter::runtimeError`.
