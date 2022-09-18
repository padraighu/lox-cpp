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
    bool isString();
    bool isNumber();
    bool isIdentifier();
    bool isNull();
    bool isBoolean();
    std::string getStringValue();
    double getNumberValue();
    bool getBooleanValue();
    static LiteralValue makeStringLiteral(std::string);
    static LiteralValue makeNumberLiteral(double);
    static LiteralValue makeNullLiteral();
    static LiteralValue makeBooleanLiteral(bool);

    friend std::ostream &operator<<(std::ostream &os, const LiteralValue &t);
};
