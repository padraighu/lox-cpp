#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "lox.hpp"
#include "scanner.hpp"

Lox::Lox()
{
    hadError = false;
}

int Lox::runFile(char *path)
{
    std::cout << "Running file" << path << std::endl;
    std::ifstream loxFile;
    std::stringstream buffer;
    loxFile.open(path);
    buffer << loxFile.rdbuf();
    loxFile.close();
    run(buffer.str());
    if (hadError)
        return 65;
    return 0;
}

void Lox::runPrompt()
{
    std::cout << "Running prompt" << std::endl;
    std::string line;
    while (true)
    {
        std::cout << "> ";
        if (std::cin.eof())
            break;
        std::getline(std::cin, line);
        run(line);
        hadError = false;
    }
}

void Lox::run(std::string source)
{
    std::cout << "Running the following lox:" << std::endl
              << std::endl;
    std::cout << source << std::endl;

    Scanner scanner(source, *this);
    auto tokens = scanner.scanTokens();
    std::cout << "Number of tokens scanned: " << tokens.size() << std::endl;

    for (auto token : tokens)
    {
        std::cout << token << std::endl;
    }
}

void Lox::error(int line, std::string message)
{
    report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    this->hadError = true;
}
