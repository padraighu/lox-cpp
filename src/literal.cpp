#include <ostream>
#include <string>
#include "literal.hpp"
#include "literaltype.hpp"

Literal::Literal(LiteralType type, std::string value)
{
    this->type = type;
    this->value = value;
}

bool Literal::isString()
{
    return type == STRING_LITERAL;
}

bool Literal::isNumber()
{
    return type == NUMBER_LITERAL;
}

bool Literal::isIdentifier()
{
    return type == IDENTIFIER_LITERAL;
}

bool Literal::isNull()
{
    return type == NULL_LITERAL;
}

std::string Literal::getStringValue()
{
    if (isString())
        return value;
    return "ERROR";
}

double Literal::getNumberValue()
{
    if (isNumber())
        return std::stod(value);
    return -1.0;
}

Literal Literal::makeStringLiteral(std::string value)
{
    return Literal(STRING_LITERAL, value);
}

Literal Literal::makeNumberLiteral(double value)
{
    return Literal(NUMBER_LITERAL, std::to_string(value));
}

Literal Literal::makeNullLiteral()
{
    return Literal(NULL_LITERAL, "NULL_LITERAL");
}

std::ostream &operator<<(std::ostream &os, const Literal &l)
{
    os << l.value;
    return os;
}
