load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "lox-library",
    srcs = glob(
        ["*.cpp"],
        exclude = ["main.cpp"],
    ),
    hdrs = glob(["*.hpp"]),
    includes = ["."],
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "lox",
    srcs = ["main.cpp"],
    deps = [":lox-library"],
)
