#pragma once
#include <string>
#include <memory>
#include <any>
#include "expr.hpp"

class AstPrinter : public Visitor
{
public:
    std::string print(const std::shared_ptr<Expr>& expr);
    std::any visitBinaryExpr(Binary expr) override;
    std::any visitGroupingExpr(Grouping expr) override;
    std::any visitLiteralExpr(Literal expr) override;
    std::any visitUnaryExpr(Unary expr) override;

std::string parenthize(const std::string& name, const std::vector<std::shared_ptr<Expr>>& expr);
};
