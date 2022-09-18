#include <gtest/gtest.h>
#include <string>
#include "lox.hpp"
#include "errorreporter.hpp"

TEST(ParserTest, TestBasic)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    std::string testLoxStmt = "2 + 2;";
    lox.run(testLoxStmt);
}
