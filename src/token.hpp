#pragma once
#include <string>
#include <iostream>
#include "tokentype.hpp"
#include "literal.hpp"

class Token
{
public:
    TokenType type;
    std::string lexeme;
    LiteralValue literal = LiteralValue::makeNullLiteral();
    int line;
    Token(TokenType, std::string, LiteralValue, int);
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};