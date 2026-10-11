load("@rules_cc//cc:cc_test.bzl", "cc_test")

[
    cc_test(
        name = name,
        size = "small",
        srcs = [name + ".cpp"],
        deps = [
            "//src:lox-library",
            "@googletest//:gtest_main",
        ],
    )
    for name in [
        "astprinter_test",
        "interpreter_test",
        "parser_test",
        "scanner_test",
    ]
]
