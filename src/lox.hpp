#pragma once
#include <string>

class Lox
{
public:
    bool hadError;

    Lox();

    int runFile(char *path);

    void runPrompt();

    void run(std::string source); // TODO can this be private

    void error(int line, std::string message);

    void report(int line, std::string where, std::string message);
};
