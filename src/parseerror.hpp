#pragma once
#include <string>
#include <exception>

class ParseError : public std::runtime_error
{
public:
    explicit ParseError(const std::string& msg) : runtime_error(msg) {}
};
