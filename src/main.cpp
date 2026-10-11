#include <iostream>
#include <memory>
#include "lox.hpp"
#include "errorreporter.hpp"

int main(int argc, char* argv[])
{
    auto errorReporter = std::make_shared<ErrorReporter>();
    Lox lox(errorReporter);

    if (argc > 2)
    {
        std::cout << "Usage: clox [script]" << std::endl;
        return 64;
    }
    else if (argc == 2)
    {
        return lox.runFile(argv[1]);
    }
    else
    {
        lox.runPrompt();
    }

    return 0;
}
