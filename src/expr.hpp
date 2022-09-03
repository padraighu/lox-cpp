#pragma once
#include <any>
#include <memory>
#include "token.hpp"

class Visitor;

class Expr
{
public:
    virtual std::any accept(Visitor& visitor) = 0;
};

class Binary : public Expr
{
public:
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
    std::any accept(Visitor& visitor);
};

class Grouping : public Expr
{
public:
    Grouping(std::shared_ptr<Expr> expression);
    std::shared_ptr<Expr> expression;
    std::any accept(Visitor& visitor);
};

class Literal : public Expr
{
public:
    Literal(LiteralValue val);
    LiteralValue val;
    std::any accept(Visitor& visitor);
};

class Unary : public Expr
{
public:
    Unary(Token op, std::shared_ptr<Expr> right);
    Token op;
    std::shared_ptr<Expr> right;
    std::any accept(Visitor& visitor);
};

class Visitor {
public:
    virtual std::any visitBinaryExpr(Binary expr) = 0;
    virtual std::any visitGroupingExpr(Grouping expr) = 0;
    virtual std::any visitLiteralExpr(Literal expr) = 0;
    virtual std::any visitUnaryExpr(Unary expr) = 0;
};

