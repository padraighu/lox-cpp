#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <memory>
#include "tokentype.hpp"
#include "scanner.hpp"
#include "lox.hpp"
#include "errorreporter.hpp"

TEST(ScannerTest, TestBasic)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);
    std::string testLox = "print 123;";
    Scanner scanner(testLox, errorReporter);
    auto tokens = scanner.scanTokens();
    EXPECT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].lexeme, "print");
    EXPECT_EQ(tokens[0].type, TokenType::PRINT);
    EXPECT_EQ(tokens[1].lexeme, "123");
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[2].lexeme, ";");
    EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
}
