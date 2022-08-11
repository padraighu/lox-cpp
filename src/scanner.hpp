#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "token.hpp"
#include "tokentype.hpp"
#include "literal.hpp"

class Scanner
{
    std::string source;
    std::vector<Token> tokens = std::vector<Token>();
    int start = 0;
    int current = 0;
    int line = 1;
    std::unordered_map<std::string, TokenType> keywords = std::unordered_map<std::string, TokenType>();

public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType);
    void addToken(TokenType, Literal);
    bool match(char);
    char peek();
    void string();
    bool isDigit(char);
    void number();
    char peekNext();
    void identifier();
    bool isAlpha(char);
    bool isAlphaNumeric(char);
};
