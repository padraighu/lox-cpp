#pragma once
#include <exception>
#include <string>

class RuntimeError : public std::runtime_error
{
public:
    Token token;
    explicit RuntimeError(Token token, const std::string& msg)
        : runtime_error(msg), token(std::move(token))
    {
    }
};
