#include <iostream>
#include "lox.hpp"

int main(int argc, char *argv[])
{
    Lox lox;

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
