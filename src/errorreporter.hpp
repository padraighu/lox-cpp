#pragma once
#include <string>

class ErrorReporter
{
public:
    bool hadError = false;
    void error(int line, std::string message);
    void report(int line, std::string where, std::string message);
};
