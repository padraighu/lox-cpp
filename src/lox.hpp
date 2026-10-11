#pragma once
#include "errorreporter.hpp"
#include <memory>
#include <string>

class Lox
{
public:
    std::shared_ptr<ErrorReporter> errorReporter;

    explicit Lox(std::shared_ptr<ErrorReporter> errorReporter);

    int runFile(char* path) const;

    void runPrompt() const;

    void run(const std::string& source) const; // TODO can this be private
};
