#include <iostream>
#include <utility>
#include "errorreporter.hpp"
#include "token.hpp"
#include "tokentype.hpp"

void ErrorReporter::error(int line, const std::string& message)
{
    report(line, "", message);
}

void ErrorReporter::report(int line, const std::string& where, const std::string& message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    this->hadError = true;
}

void ErrorReporter::error(const Token& token, const std::string& message)
{
    if (token.type == TokenType::LEOF) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void ErrorReporter::runtimeError(const RuntimeError& error)
{
    std::cerr << error.what() << "\n[line " << error.token.line << "]" << std::endl;
    hadRuntimeError = true;
}
