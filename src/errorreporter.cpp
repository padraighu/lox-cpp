#include <iostream>
#include "errorreporter.hpp"

void ErrorReporter::error(int line, std::string message)
{
    report(line, "", message);
}

void ErrorReporter::report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    this->hadError = true;
}
