#include <gtest/gtest.h>
#include <string>
#include "lox.hpp"
#include "errorreporter.hpp"

TEST(InterpreterTest, TestArithmetic)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    std::string testLoxStmt = "2 + 2;";
    lox.run(testLoxStmt);
}

TEST(InterpreterTest, TestComparison)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    std::string testLoxStmt = "1 < 2;";
    lox.run(testLoxStmt);
}

TEST(InterpreterTest, TestParseErrorSkipsInterpreter)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    lox.run("(1 +");
    EXPECT_TRUE(errorReporter->hadError);
    EXPECT_FALSE(errorReporter->hadRuntimeError);
}

static std::string runAndCapture(const std::string& source)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    testing::internal::CaptureStdout();
    lox.run(source);
    return testing::internal::GetCapturedStdout();
}

TEST(InterpreterTest, TestStringConcatenation)
{
    EXPECT_EQ(runAndCapture("\"a\" + \"b\""), "ab\n");
}

TEST(InterpreterTest, TestPrintNil)
{
    EXPECT_EQ(runAndCapture("nil"), "nil\n");
}

TEST(InterpreterTest, TestNumberPrecision)
{
    EXPECT_EQ(runAndCapture("0.1"), "0.1\n");
    EXPECT_EQ(runAndCapture("1 / 3 * 3"), "1\n");
    EXPECT_EQ(runAndCapture("1 / 3"), "0.3333333333333333\n");
    EXPECT_EQ(runAndCapture("2.5 * 2"), "5\n");
    EXPECT_EQ(runAndCapture("-0.5"), "-0.5\n");
}

TEST(InterpreterTest, TestEquality)
{
    EXPECT_EQ(runAndCapture("true == true"), "true\n");
    EXPECT_EQ(runAndCapture("true == false"), "false\n");
    EXPECT_EQ(runAndCapture("nil == nil"), "true\n");
    EXPECT_EQ(runAndCapture("nil == false"), "false\n");
    EXPECT_EQ(runAndCapture("1 == 1.0"), "true\n");
    EXPECT_EQ(runAndCapture("\"1\" == 1"), "false\n");
    EXPECT_EQ(runAndCapture("\"ab\" != \"ab\""), "false\n");
}

TEST(InterpreterTest, TestUnary)
{
    EXPECT_EQ(runAndCapture("-3"), "-3\n");
    EXPECT_EQ(runAndCapture("!true"), "false\n");
    EXPECT_EQ(runAndCapture("!nil"), "true\n");
    EXPECT_EQ(runAndCapture("!0"), "false\n");
}

TEST(InterpreterTest, TestNegateNonNumberIsRuntimeError)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    lox.run("-\"x\"");
    EXPECT_TRUE(errorReporter->hadRuntimeError);
}
