#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>
#include "lox.hpp"
#include "scanner.hpp"
#include "errorreporter.hpp"
#include "parser.hpp"
#include "astprinter.hpp"
#include "interpreter.hpp"

Lox::Lox(std::shared_ptr<ErrorReporter> errorReporter)
    : errorReporter(std::move(errorReporter)), interpreter(this->errorReporter)
{
}

int Lox::runFile(char* path)
{
    std::cout << "Running file" << path << std::endl;
    std::ifstream loxFile;
    std::stringstream buffer;
    loxFile.open(path);
    buffer << loxFile.rdbuf();
    loxFile.close();
    run(buffer.str());
    if (errorReporter->hadError) return 65;
    if (errorReporter->hadRuntimeError) return 70;
    return 0;
}

void Lox::runPrompt()
{
    std::cout << "Running prompt" << std::endl;
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line))
    {
        run(line);
        errorReporter->hadError = false;
        std::cout << "> ";
    }
    std::cout << std::endl;
}

void Lox::run(const std::string& source)
{
    Scanner scanner(source, errorReporter);
    auto tokens = scanner.scanTokens();
    Parser parser(tokens, errorReporter);
    auto expression = parser.parse();
    if (errorReporter->hadError) return;
    interpreter.interpret(expression);
}
