#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "lox.hpp"
#include "scanner.hpp"
#include "errorreporter.hpp"
#include "parser.hpp"
#include "expr.hpp"
#include "astprinter.hpp"
#include "interpreter.hpp"

Lox::Lox(std::shared_ptr<ErrorReporter> errorReporter)
{
    this->errorReporter = std::move(errorReporter);
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
    if (errorReporter->hadError)
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
        errorReporter->hadError = false;
    }
}

void Lox::run(const std::string& source)
{
    std::cout << "Running the following lox:" << std::endl
              << std::endl;
    std::cout << source << std::endl;

    Scanner scanner(source, errorReporter);
    auto tokens = scanner.scanTokens();
    Parser parser(tokens);
    auto expression = parser.parse();
    AstPrinter printer;
    auto result = printer.print(expression);
    std::cout << "AstPrinter output:" << std::endl;
    std::cout << result << std::endl;
    Interpreter interpreter;
    interpreter.interpret(expression);
}
