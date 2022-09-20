#include <utility>
#include "token.hpp"
#include "literal.hpp"
#include "tokentype.hpp"

Token::Token(TokenType type, std::string lexeme, LiteralValue literal, int line)
{
    this->type = type;
    this->lexeme = std::move(lexeme);
    this->literal = std::move(literal);
    this->line = line;
}

std::ostream &operator<<(std::ostream &os, const Token &t)
{
    os << t.type << " '" << t.lexeme << "' " << t.literal;
    return os;
}
