#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <string>
#include <utility>
#include "literal.hpp"

LiteralValue::LiteralValue(decltype(value) value) : value(std::move(value)) {}

bool LiteralValue::isString() const
{
    return std::holds_alternative<std::string>(value);
}

bool LiteralValue::isNumber() const
{
    return std::holds_alternative<double>(value);
}

bool LiteralValue::isNull() const
{
    return std::holds_alternative<std::monostate>(value);
}

bool LiteralValue::isBoolean() const
{
    return std::holds_alternative<bool>(value);
}

// Callers must check the type first; these throw std::bad_variant_access otherwise.
const std::string& LiteralValue::getStringValue() const
{
    return std::get<std::string>(value);
}

double LiteralValue::getNumberValue() const
{
    return std::get<double>(value);
}

bool LiteralValue::getBooleanValue() const
{
    return std::get<bool>(value);
}

std::string LiteralValue::toString() const
{
    if (isNull()) return "nil";
    if (isBoolean()) return getBooleanValue() ? "true" : "false";
    if (isString()) return getStringValue();

    // Fewest significant digits that round-trip, so 0.1 prints as "0.1" and 3.0 as "3".
    // (std::to_chars does this directly but needs macOS 13.3+.)
    double number = getNumberValue();
    char buf[32];
    for (int precision = 15; precision <= 17; precision++)
    {
        std::snprintf(buf, sizeof(buf), "%.*g", precision, number);
        if (std::strtod(buf, nullptr) == number) break;
    }
    return buf;
}

LiteralValue LiteralValue::makeStringLiteral(std::string value)
{
    return LiteralValue(std::move(value));
}

LiteralValue LiteralValue::makeNumberLiteral(double value)
{
    return LiteralValue(value);
}

LiteralValue LiteralValue::makeNullLiteral()
{
    return LiteralValue(std::monostate{});
}

LiteralValue LiteralValue::makeBooleanLiteral(bool value)
{
    return LiteralValue(value);
}

bool LiteralValue::operator==(const LiteralValue& other) const
{
    return value == other.value;
}

bool LiteralValue::operator!=(const LiteralValue& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const LiteralValue& l)
{
    return os << l.toString();
}
