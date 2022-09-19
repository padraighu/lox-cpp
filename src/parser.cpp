#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include "parser.hpp"
#include "tokentype.hpp"
#include "token.hpp"
#include "expr.hpp"
#include "literal.hpp"

Parser::Parser(std::vector<Token> tokens)
{
    this->tokens = std::move(tokens);
}

std::shared_ptr<Expr> Parser::expression()
{
    return equality();
}

std::shared_ptr<Expr> Parser::equality()
{
    std::shared_ptr<Expr> expr = comparison();
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}))
    {
        Token op = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::comparison()
{
    std::shared_ptr<Expr> expr = term();
    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token op = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::term()
{
    std::shared_ptr<Expr> expr = factor();
    while (match({TokenType::MINUS, TokenType::PLUS}))
    {
        Token op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::factor()
{
    std::shared_ptr<Expr> expr = unary();
    while (match({TokenType::SLASH, TokenType::STAR}))
    {
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::unary()
{
    if (match({TokenType::BANG, TokenType::MINUS}))
    {
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<Unary>(op, right);
    }
    return primary();
}

std::shared_ptr<Expr> Parser::primary()
{
    // TODO create false and true literal values
    if (match({TokenType::FALSE})) return std::make_shared<Literal>(LiteralValue::makeNullLiteral());
    if (match({TokenType::TRUE})) return std::make_shared<Literal>(LiteralValue::makeNullLiteral());
    if (match({TokenType::NIL})) return std::make_shared<Literal>(LiteralValue::makeNullLiteral());

    if (match({TokenType::NUMBER, TokenType::STRING}))
    {
        return std::make_shared<Literal>(previous().literal);
    }

    if (match({TokenType::LEFT_PAREN}))
    {
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<Grouping>(expr);
    }

    // TODO exception 
    return nullptr;
}

std::shared_ptr<Expr> Parser::parse()
{
    // TODO try block
    return expression();
}

bool Parser::match(const std::vector<TokenType>& types)
{
    for (const auto t: types)
    {
        if (check(t))
        {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type)
{
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance()
{
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd()
{
    return peek().type == TokenType::LEOF;
}

Token Parser::peek()
{
    return tokens[current];
}

Token Parser::previous()
{
    return tokens[current - 1];
}

Token Parser::consume(TokenType type, const std::string& message)
{
    if (check(type)) return advance();

    // TODO throw error etc.
    // return nullptr;
}
