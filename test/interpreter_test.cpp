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
