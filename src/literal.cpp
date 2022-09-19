#include <ostream>
#include <string>
#include <utility>
#include "literal.hpp"
#include "literaltype.hpp"

LiteralValue::LiteralValue(LiteralType type, std::string value)
{
    this->type = type;
    this->value = std::move(value);
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

bool LiteralValue::isBoolean()
{
    return type == BOOLEAN_LITERAL;
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

bool LiteralValue::getBooleanValue()
{
    if (isBoolean())
    {
        if (value == "true") return true;
        if (value == "false") return false;
    }
    return false;
}

LiteralValue LiteralValue::makeStringLiteral(std::string value)
{
    return {STRING_LITERAL, std::move(value)};
}

LiteralValue LiteralValue::makeNumberLiteral(double value)
{
    return {NUMBER_LITERAL, std::to_string(value)};
}

LiteralValue LiteralValue::makeNullLiteral()
{
    return {NULL_LITERAL, "NULL_LITERAL"};
}

LiteralValue LiteralValue::makeBooleanLiteral(bool value)
{
    std::string strVal = value ? "true" : "false";
    return {BOOLEAN_LITERAL, strVal};
}

std::ostream &operator<<(std::ostream &os, const LiteralValue &l)
{
    os << l.value;
    return os;
}
