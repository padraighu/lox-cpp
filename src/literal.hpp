#pragma once
#include <ostream>
#include <string>
#include "literaltype.hpp"

class Literal
{
    LiteralType type;
    std::string value;
    Literal(LiteralType, std::string);

public:
    bool isString();
    bool isNumber();
    bool isIdentifier();
    bool isNull();
    std::string getStringValue();
    double getNumberValue();
    static Literal makeStringLiteral(std::string);
    static Literal makeNumberLiteral(double);
    static Literal makeNullLiteral();

    friend std::ostream &operator<<(std::ostream &os, const Literal &t);
};
