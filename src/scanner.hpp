#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "token.hpp"
#include "tokentype.hpp"
#include "literal.hpp"
#include "errorreporter.hpp"

class Scanner
{
    std::string source;
    std::vector<Token> tokens = std::vector<Token>();
    std::size_t start = 0;
    std::size_t current = 0;
    int line = 1;
    std::unordered_map<std::string, TokenType> keywords =
        std::unordered_map<std::string, TokenType>();
    std::shared_ptr<ErrorReporter> errorReporter;

public:
    Scanner(std::string source, std::shared_ptr<ErrorReporter> errorReporter);
    std::vector<Token> scanTokens();

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType);
    void addToken(TokenType, LiteralValue);
    bool match(char);
    char peek();
    void string();
    static bool isDigit(char);
    void number();
    char peekNext();
    void identifier();
    static bool isAlpha(char);
    static bool isAlphaNumeric(char);
};
