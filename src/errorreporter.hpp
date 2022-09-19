#pragma once
#include <string>

class ErrorReporter
{
public:
    bool hadError = false;
    void error(int line, const std::string& message);
    void report(int line, const std::string& where, const std::string& message);
};
