# Lox Interpreter

### Build

This project uses Bazel to build.

To build the interpreter:
```
bazel build --cxxopt='-std=c++17' //src:lox
```

The binary is located at `bazel-bin/src/lox`

To run tests:
```
bazel test --test_output=all --cxxopt='-std=c++17' //test:scanner_test
```
