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
{
    this->errorReporter = std::move(errorReporter);
}

int Lox::runFile(char* path) const
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

void Lox::runPrompt() const
{
    std::cout << "Running prompt" << std::endl;
    std::string line;
    while (true)
    {
        std::cout << "> ";
        if (std::cin.eof()) break;
        std::getline(std::cin, line);
        run(line);
        errorReporter->hadError = false;
    }
}

void Lox::run(const std::string& source) const
{
    Scanner scanner(source, errorReporter);
    auto tokens = scanner.scanTokens();
    Parser parser(tokens, errorReporter);
    auto expression = parser.parse();
    if (errorReporter->hadError) return;
    Interpreter interpreter(errorReporter);
    interpreter.interpret(expression);
}
