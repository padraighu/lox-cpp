#include "scanner.hpp"
#include "token.hpp"
#include "tokentype.hpp"
#include "literal.hpp"
#include "lox.hpp"
#include <string>
#include <unordered_map>

Scanner::Scanner(std::string source)
{
    this->source = source;
    keywords.insert(std::pair<std::string, TokenType>("and", AND));
    keywords.insert(std::pair<std::string, TokenType>("class", CLASS));
    keywords.insert(std::pair<std::string, TokenType>("else", ELSE));
    keywords.insert(std::pair<std::string, TokenType>("false", FALSE));
    keywords.insert(std::pair<std::string, TokenType>("for", FOR));
    keywords.insert(std::pair<std::string, TokenType>("fun", FUN));
    keywords.insert(std::pair<std::string, TokenType>("if", IF));
    keywords.insert(std::pair<std::string, TokenType>("nil", NIL));
    keywords.insert(std::pair<std::string, TokenType>("or", OR));
    keywords.insert(std::pair<std::string, TokenType>("print", PRINT));
    keywords.insert(std::pair<std::string, TokenType>("return", RETURN));
    keywords.insert(std::pair<std::string, TokenType>("super", SUPER));
    keywords.insert(std::pair<std::string, TokenType>("this", THIS));
    keywords.insert(std::pair<std::string, TokenType>("true", TRUE));
    keywords.insert(std::pair<std::string, TokenType>("var", VAR));
    keywords.insert(std::pair<std::string, TokenType>("while", WHILE));
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    auto tok = Token(LEOF, "", Literal::makeNullLiteral(), line);
    tokens.push_back(tok);
    return tokens;
}

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
    case '(':
        addToken(LEFT_PAREN);
        break;
    case ')':
        addToken(RIGHT_PAREN);
        break;
    case '{':
        addToken(LEFT_BRACE);
        break;
    case '}':
        addToken(RIGHT_BRACE);
        break;
    case ',':
        addToken(COMMA);
        break;
    case '.':
        addToken(DOT);
        break;
    case '-':
        addToken(MINUS);
        break;
    case '+':
        addToken(PLUS);
        break;
    case ';':
        addToken(SEMICOLON);
        break;
    case '*':
        addToken(STAR);
        break;
    case '!':
        addToken(match('=') ? BANG_EQUAL : BANG);
        break;
    case '=':
        addToken(match('=') ? EQUAL_EQUAL : EQUAL);
        break;
    case '<':
        addToken(match('=') ? LESS_EQUAL : LESS);
        break;
    case '>':
        addToken(match('=') ? GREATER_EQUAL : GREATER);
        break;
    case '/':
        if (match('/'))
        {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd())
                advance();
        }
        else
        {
            addToken(SLASH);
        }
        break;

    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;

    case '\n':
        line++;
        break;

    case '"':
        string();
        break;

    default:
        if (isDigit(c))
        {
            number();
        }
        else if (isAlpha(c))
        {
            identifier();
        }
        else
        {
            // TODO Lox.error(line, "Unexpected character.");
        }
        break;
    }
}

char Scanner::advance()
{
    return source.at(current++);
}

void Scanner::addToken(TokenType type)
{
    addToken(type, Literal::makeNullLiteral());
}

void Scanner::addToken(TokenType type, Literal literal)
{
    std::string text = source.substr(start, current - start);
    auto tok = Token(type, text, literal, line);
    tokens.push_back(tok);
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (source.at(current) != expected)
        return false;

    current++;
    return true;
}

char Scanner::peek()
{
    if (isAtEnd())
        return '\0';
    return source.at(current);
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (isAtEnd())
    {
        //  TODO Lox.error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    auto value = source.substr(start + 1, current - start - 1);
    auto stringLiteral = Literal::makeStringLiteral(value);
    addToken(STRING, stringLiteral);
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void Scanner::number()
{
    while (isDigit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        // Consume the "."
        advance();

        while (isDigit(peek()))
            advance();
    }

    auto valueStr = source.substr(start, current - start);
    auto value = std::stod(valueStr);
    auto numberLiteral = Literal::makeNumberLiteral(value);
    addToken(NUMBER, numberLiteral);
}

char Scanner::peekNext()
{
    if (current + 1 >= source.length())
        return '\0';
    return source.at(current + 1);
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek()))
        advance();

    auto text = source.substr(start, current - start);
    TokenType type;
    if (keywords.count(text) == 0)
    {
        type = IDENTIFIER;
    }
    else
    {
        type = keywords.at(text);
    }
    addToken(type);
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}
