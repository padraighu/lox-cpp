#include <string>
#include <any>
#include <vector>
#include <memory>
#include "astprinter.hpp"
#include "expr.hpp"

// Borrowed heavily from https://github.com/the-lambda-way/CppLox/blob/master/chapter5

std::string AstPrinter::print(std::shared_ptr<Expr> expr)
{
    return std::any_cast<std::string>(expr->accept(*this));
}

std::any AstPrinter::visitBinaryExpr(Binary expr)
{
    std::vector<std::shared_ptr<Expr>> expressions = {expr.left, expr.right};
    return parenthize(expr.op.lexeme, expressions);
}

std::any AstPrinter::visitGroupingExpr(Grouping expr)
{
    std::vector<std::shared_ptr<Expr>> expressions = {expr.expression};
    return parenthize("group", expressions);
}

std::any AstPrinter::visitLiteralExpr(Literal expr)
{
    if (expr.val.isNull()) return "nil";
    if (expr.val.isNumber()) return std::to_string(expr.val.getNumberValue());
    if (expr.val.isString()) return expr.val.getStringValue();
    if (expr.val.isBoolean()) return expr.val.getBooleanValue() ? "true" : "false";
    return "Identifier TODO!!"; // TODO
}

std::any AstPrinter::visitUnaryExpr(Unary expr)
{
    std::vector<std::shared_ptr<Expr>> expressions = {expr.right};
    return parenthize(expr.op.lexeme, expressions);
}


std::string AstPrinter::parenthize(std::string name, std::vector<std::shared_ptr<Expr>> expr)
{
    std::string result = "(" + name;
    // https://stackoverflow.com/questions/7230621/how-can-i-iterate-over-a-packed-variadic-template-argument-list
    for (auto const &e: expr) {
        result += " " + print(e);
    }
    result += ")";
    return result;
}
