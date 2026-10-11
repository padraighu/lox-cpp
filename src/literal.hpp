#pragma once
#include <ostream>
#include <string>
#include <variant>

class LiteralValue
{
    std::variant<std::monostate, bool, double, std::string> value;
    explicit LiteralValue(decltype(value) value);

public:
    bool isString() const;
    bool isNumber() const;
    bool isNull() const;
    bool isBoolean() const;
    const std::string& getStringValue() const;
    double getNumberValue() const;
    bool getBooleanValue() const;
    std::string toString() const;
    static LiteralValue makeStringLiteral(std::string);
    static LiteralValue makeNumberLiteral(double);
    static LiteralValue makeNullLiteral();
    static LiteralValue makeBooleanLiteral(bool);

    // Lox equality: same type and same value; nil == nil.
    bool operator==(const LiteralValue& other) const;
    bool operator!=(const LiteralValue& other) const;

    friend std::ostream& operator<<(std::ostream& os, const LiteralValue& l);
};
