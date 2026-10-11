#include <memory>
#include <utility>
#include "interpreter.hpp"
#include "expr.hpp"
#include "literal.hpp"
#include "tokentype.hpp"
#include "token.hpp"
#include "errorreporter.hpp"
#include "runtimeerror.hpp"

Interpreter::Interpreter(std::shared_ptr<ErrorReporter> errorReporter)
{
    this->errorReporter = std::move(errorReporter);
}

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
        if (expr.op.type == TokenType::MINUS)
        {
            checkNumberOperand(expr.op, right);
            return LiteralValue::makeNumberLiteral(-right.getNumberValue());
        }
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
        checkNumberOperands(expr.op, left, right);
        return LiteralValue::makeNumberLiteral(left.getNumberValue() - right.getNumberValue());
    case TokenType::SLASH:
        checkNumberOperands(expr.op, left, right);
        return LiteralValue::makeNumberLiteral(left.getNumberValue() / right.getNumberValue());
    case TokenType::STAR:
        checkNumberOperands(expr.op, left, right);
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
        throw RuntimeError(expr.op, "Operands must be two numbers or two strings.");
    case TokenType::GREATER:
        checkNumberOperands(expr.op, left, right);
        return LiteralValue::makeBooleanLiteral(left.getNumberValue() > right.getNumberValue());
    case TokenType::GREATER_EQUAL:
        checkNumberOperands(expr.op, left, right);
        return LiteralValue::makeBooleanLiteral(left.getNumberValue() >= right.getNumberValue());
    case TokenType::LESS:
        checkNumberOperands(expr.op, left, right);
        return LiteralValue::makeBooleanLiteral(left.getNumberValue() < right.getNumberValue());
    case TokenType::LESS_EQUAL:
        checkNumberOperands(expr.op, left, right);
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
    try
    {
        auto value = std::any_cast<LiteralValue>(evaluate(expression));
        std::cout << value << std::endl;
    }
    catch (RuntimeError& re)
    {
        errorReporter->runtimeError(re);
    }
}

void Interpreter::checkNumberOperand(Token operatorTok, LiteralValue operand)
{
    if (!operand.isNumber())
        throw RuntimeError(std::move(operatorTok), "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token operatorTok, LiteralValue left, LiteralValue right)
{
    if (!left.isNumber() || !right.isNumber())
        throw RuntimeError(std::move(operatorTok), "Operands must be a numbers.");
}
