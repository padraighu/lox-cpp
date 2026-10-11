#include <ostream>
#include <string>
#include <utility>
#include <cmath>
#include "literal.hpp"
#include "literaltype.hpp"

LiteralValue::LiteralValue(LiteralType type, std::string value)
{
    this->type = type;
    this->value = std::move(value);
}

bool LiteralValue::isString() const
{
    return type == STRING_LITERAL;
}

bool LiteralValue::isNumber() const
{
    return type == NUMBER_LITERAL;
}

bool LiteralValue::isIdentifier() const
{
    return type == IDENTIFIER_LITERAL;
}

bool LiteralValue::isNull() const
{
    return type == NULL_LITERAL;
}

bool LiteralValue::isBoolean() const
{
    return type == BOOLEAN_LITERAL;
}

std::string LiteralValue::getStringValue() const
{
    if (isString()) return value;
    return "ERROR";
}

double LiteralValue::getNumberValue() const
{
    if (isNumber()) return std::stod(value);
    return -1.0;
}

bool LiteralValue::getBooleanValue() const
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

std::ostream& operator<<(std::ostream& os, const LiteralValue& l)
{
    if (l.isNull())
        os << "nil";
    else if (l.isNumber())
    {
        double intpart;
        auto val = l.getNumberValue();
        if (std::modf(val, &intpart) == 0.0)
        {
            auto s = std::to_string(val);
            auto i = s.find('.', 0);
            os << s.substr(0, i);
        }
        else
            os << l.value;
    }
    else
        os << l.value;
    return os;
}
