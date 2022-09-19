#pragma once
#include <string>
#include "token.hpp"

class ErrorReporter
{
public:
    bool hadError = false;
    void error(int line, const std::string& message);
    void report(int line, const std::string& where, const std::string& message);
    void error(Token token, const std::string& message);
};
