#pragma once
#include <string>
#include <memory>
#include "expr.hpp"

class AstPrinter : public Visitor
{
public:
    std::string print(std::shared_ptr<Expr> expr);
    std::any visitBinaryExpr(Binary expr) override;
    std::any visitGroupingExpr(Grouping expr) override;
    std::any visitLiteralExpr(Literal expr) override;
    std::any visitUnaryExpr(Unary expr) override;

std::string parenthize(std::string name, std::vector<std::shared_ptr<Expr>> expr);
};
