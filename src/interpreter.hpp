#pragma once
#include <any>
#include <memory>
#include <string>
#include "expr.hpp"
#include "literal.hpp"

class Interpreter : public Visitor
{
public:
    std::any visitLiteralExpr(Literal expr) override;
    std::any visitGroupingExpr(Grouping expr) override;
    std::any visitUnaryExpr(Unary expr) override;
    std::any visitBinaryExpr(Binary expr) override;
    void interpret(const std::shared_ptr<Expr>& expression);

private:
    std::any evaluate(const std::shared_ptr<Expr>& expr);
    bool isTruthy(LiteralValue val);
    bool isEqual(LiteralValue a, LiteralValue b);
};
