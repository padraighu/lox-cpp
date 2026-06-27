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
