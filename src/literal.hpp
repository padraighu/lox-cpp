#pragma once
#include <ostream>
#include <string>
#include "literaltype.hpp"

class LiteralValue
{
    LiteralType type;
    std::string value;
    LiteralValue(LiteralType, std::string);

public:
    bool isString() const;
    bool isNumber() const;
    bool isIdentifier() const;
    bool isNull() const;
    bool isBoolean() const;
    std::string getStringValue() const;
    double getNumberValue() const;
    bool getBooleanValue() const;
    static LiteralValue makeStringLiteral(std::string);
    static LiteralValue makeNumberLiteral(double);
    static LiteralValue makeNullLiteral();
    static LiteralValue makeBooleanLiteral(bool);

    friend std::ostream& operator<<(std::ostream& os, const LiteralValue& l);
};
