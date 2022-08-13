#include <ostream>
#include <string>
#include "literal.hpp"
#include "literaltype.hpp"

LiteralValue::LiteralValue(LiteralType type, std::string value)
{
    this->type = type;
    this->value = value;
}

bool LiteralValue::isString()
{
    return type == STRING_LITERAL;
}

bool LiteralValue::isNumber()
{
    return type == NUMBER_LITERAL;
}

bool LiteralValue::isIdentifier()
{
    return type == IDENTIFIER_LITERAL;
}

bool LiteralValue::isNull()
{
    return type == NULL_LITERAL;
}

std::string LiteralValue::getStringValue()
{
    if (isString())
        return value;
    return "ERROR";
}

double LiteralValue::getNumberValue()
{
    if (isNumber())
        return std::stod(value);
    return -1.0;
}

LiteralValue LiteralValue::makeStringLiteral(std::string value)
{
    return LiteralValue(STRING_LITERAL, value);
}

LiteralValue LiteralValue::makeNumberLiteral(double value)
{
    return LiteralValue(NUMBER_LITERAL, std::to_string(value));
}

LiteralValue LiteralValue::makeNullLiteral()
{
    return LiteralValue(NULL_LITERAL, "NULL_LITERAL");
}

std::ostream &operator<<(std::ostream &os, const LiteralValue &l)
{
    os << l.value;
    return os;
}
