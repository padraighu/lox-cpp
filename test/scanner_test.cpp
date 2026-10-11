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
    EXPECT_EQ(tokens.size(), 4u);
    EXPECT_EQ(tokens[0].lexeme, "print");
    EXPECT_EQ(tokens[0].type, TokenType::PRINT);
    EXPECT_EQ(tokens[1].lexeme, "123");
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[2].lexeme, ";");
    EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
}

TEST(ScannerTest, TestStringLiteralExcludesQuotes)
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Scanner scanner("\"abc\"", errorReporter);
    auto tokens = scanner.scanTokens();
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0].type, TokenType::STRING);
    EXPECT_EQ(tokens[0].lexeme, "\"abc\"");
    EXPECT_EQ(tokens[0].literal.getStringValue(), "abc");
}
