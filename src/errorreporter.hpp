#pragma once
#include <string>
#include "token.hpp"
#include "runtimeerror.hpp"

class ErrorReporter
{
public:
    bool hadError = false;
    bool hadRuntimeError = false;
    void error(int line, const std::string& message);
    void report(int line, const std::string& where, const std::string& message);
    void error(const Token& token, const std::string& message);
    void runtimeError(const RuntimeError& error);
};
