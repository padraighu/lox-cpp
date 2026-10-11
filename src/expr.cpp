#include <memory>
#include <any>
#include <utility>
#include "expr.hpp"

Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
    : op(std::move(op))
{
    this->left = std::move(left);
    this->right = std::move(right);
}
std::any Binary::accept(Visitor& visitor)
{
    return visitor.visitBinaryExpr(*this);
}

Grouping::Grouping(std::shared_ptr<Expr> expression)
{
    this->expression = std::move(expression);
}
std::any Grouping::accept(Visitor& visitor)
{
    return visitor.visitGroupingExpr(*this);
}

Literal::Literal(LiteralValue val) : val(std::move(val)) {}
std::any Literal::accept(Visitor& visitor)
{
    return visitor.visitLiteralExpr(*this);
}

Unary::Unary(Token op, std::shared_ptr<Expr> right) : op(std::move(op))
{
    this->right = std::move(right);
}
std::any Unary::accept(Visitor& visitor)
{
    return visitor.visitUnaryExpr(*this);
}
