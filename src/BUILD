cc_library(
    name = "lox-library",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.hpp"]),
    includes = ["."],
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "lox",
    srcs = ["main.cpp"],
    deps = [
        ":lox-library",
    ],
)
