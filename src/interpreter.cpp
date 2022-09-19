#include <memory>
#include "interpreter.hpp"
#include "expr.hpp"
#include "literal.hpp"
#include "tokentype.hpp"

std::any Interpreter::visitLiteralExpr(Literal expr)
{
    return expr.val;
}

std::any Interpreter::visitGroupingExpr(Grouping expr)
{
    return evaluate(expr.expression);
}

std::any Interpreter::visitUnaryExpr(Unary expr)
{
    auto right = std::any_cast<LiteralValue>(evaluate(expr.right));
    if (right.isNumber())
    {
        if (expr.op.type == TokenType::MINUS) return LiteralValue::makeNumberLiteral(-right.getNumberValue());
    }
    if (expr.op.type == TokenType::BANG) return LiteralValue::makeBooleanLiteral(isTruthy(right));
    return nullptr;
}

std::any Interpreter::visitBinaryExpr(Binary expr)
{
    auto left = std::any_cast<LiteralValue>(evaluate(expr.left));
    auto right = std::any_cast<LiteralValue>(evaluate(expr.right));
    switch (expr.op.type)
    {
        case TokenType::MINUS:
            return LiteralValue::makeNumberLiteral(left.getNumberValue() - right.getNumberValue());
        case TokenType::SLASH:
            return LiteralValue::makeNumberLiteral(left.getNumberValue() / right.getNumberValue());
        case TokenType::STAR:
            return LiteralValue::makeNumberLiteral(left.getNumberValue() * right.getNumberValue());
        case TokenType::PLUS:
            if (left.isNumber() && right.isNumber())
            {
                return LiteralValue::makeNumberLiteral(left.getNumberValue() + right.getNumberValue());
            }
            if (left.isString() && right.isString())
            {
                return LiteralValue::makeStringLiteral(left.getStringValue() + right.getStringValue());
            }
            break;
        case TokenType::GREATER:
            return LiteralValue::makeBooleanLiteral(left.getNumberValue() > right.getNumberValue());
        case TokenType::GREATER_EQUAL:
            return LiteralValue::makeBooleanLiteral(left.getNumberValue() >= right.getNumberValue());
        case TokenType::LESS:
            return LiteralValue::makeBooleanLiteral(left.getNumberValue() < right.getNumberValue());
        case TokenType::LESS_EQUAL:
            return LiteralValue::makeBooleanLiteral(left.getNumberValue() <= right.getNumberValue());
        case TokenType::BANG_EQUAL:
            return LiteralValue::makeBooleanLiteral(!isEqual(left, right));
        case TokenType::EQUAL_EQUAL:
            return LiteralValue::makeBooleanLiteral(isEqual(left, right));
        default:
            return LiteralValue::makeNullLiteral();
    }
}

std::any Interpreter::evaluate(const std::shared_ptr<Expr>& expr)
{
    return expr->accept(*this);
}

bool Interpreter::isTruthy(LiteralValue val)
{
    if (val.isNull()) return false;
    if (val.isBoolean()) return val.getBooleanValue();
    return true;
}

bool Interpreter::isEqual(LiteralValue a, LiteralValue b)
{
    if (a.isNull() && b.isNull()) return true;
    if (a.isNull()) return false;
    if (a.isNumber() && b.isNumber()) return a.getNumberValue() == b.getNumberValue();
    if (a.isString() && b.isString()) return a.getStringValue() == b.getStringValue();
    return false;
}

void Interpreter::interpret(const std::shared_ptr<Expr>& expression)
{
    auto value = std::any_cast<LiteralValue>(evaluate(expression));
    std::cout << value << std::endl;
}
