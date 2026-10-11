#pragma once
#include "errorreporter.hpp"
#include "interpreter.hpp"
#include <memory>
#include <string>

class Lox
{
public:
    std::shared_ptr<ErrorReporter> errorReporter;

    explicit Lox(std::shared_ptr<ErrorReporter> errorReporter);

    int runFile(char* path);

    void runPrompt();

    void run(const std::string& source); // TODO can this be private

private:
    // One interpreter for the whole session, so state (e.g. global variables)
    // persists across REPL lines. Declared after errorReporter, which it uses.
    Interpreter interpreter;
};
