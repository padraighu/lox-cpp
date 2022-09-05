#pragma once
#include "errorreporter.hpp"
#include <memory>
#include <string>

class Lox
{
public:
    std::shared_ptr<ErrorReporter> errorReporter;

    Lox(std::shared_ptr<ErrorReporter> errorReporter);

    int runFile(char *path);

    void runPrompt();

    void run(std::string source); // TODO can this be private
};
