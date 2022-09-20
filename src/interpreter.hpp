#pragma once
#include <any>
#include <memory>
#include <string>
#include <exception>
#include <utility>
#include "expr.hpp"
#include "literal.hpp"
#include "token.hpp"
#include "errorreporter.hpp"

class Interpreter : public Visitor
{
public:
    explicit Interpreter(std::shared_ptr<ErrorReporter> errorReporter);
    std::any visitLiteralExpr(Literal expr) override;
    std::any visitGroupingExpr(Grouping expr) override;
    std::any visitUnaryExpr(Unary expr) override;
    std::any visitBinaryExpr(Binary expr) override;
    void interpret(const std::shared_ptr<Expr>& expression);

private:
    std::shared_ptr<ErrorReporter> errorReporter;
    std::any evaluate(const std::shared_ptr<Expr>& expr);
    static bool isTruthy(LiteralValue val);
    static bool isEqual(LiteralValue a, LiteralValue b);
    static void checkNumberOperand(Token operatorTok, LiteralValue operand);
    static void checkNumberOperands(Token operatorTok, LiteralValue left, LiteralValue right);
};
