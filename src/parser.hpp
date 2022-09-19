#pragma once
#include <vector>
#include <memory>
#include "tokentype.hpp"
#include "token.hpp"
#include "expr.hpp"

class Parser
{
private:
    std::vector<Token> tokens;
    int current = 0;
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Token consume(TokenType type, const std::string& message);

public:
    explicit Parser(std::vector<Token> tokens);
    std::shared_ptr<Expr> parse();
};
