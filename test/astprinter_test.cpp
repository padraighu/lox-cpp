#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "expr.hpp"
#include "token.hpp"
#include "tokentype.hpp"
#include "literal.hpp"
#include "astprinter.hpp"

TEST(AstPrinterTest, TestBasic)
{
    auto left =
        std::make_shared<Unary>(Token(TokenType::MINUS, "-", LiteralValue::makeNullLiteral(), 1),
                                std::make_shared<Literal>(LiteralValue::makeNumberLiteral(123.0)));
    Token op = Token(TokenType::STAR, "*", LiteralValue::makeNullLiteral(), 1);
    auto right = std::make_shared<Grouping>(
        std::make_shared<Literal>(LiteralValue::makeNumberLiteral(45.67)));
    auto expr = std::make_shared<Binary>(left, op, right);
    AstPrinter printer;
    std::string result = printer.print(expr);
    EXPECT_EQ(result, "(* (- 123) (group 45.67))");
}
