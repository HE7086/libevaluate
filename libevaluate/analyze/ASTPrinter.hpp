#pragma once

#include "ASTVisitor.hpp"
#include "util/Code.hpp"
#include "AST.hpp"
#include <concepts>

namespace evaluate {

class ASTPrinter : public ASTVisitor {
    private:
    const Code& code;
    size_t count = 0;

    public:
    explicit ASTPrinter(const Code& code);
    void visit(const VALUE& node) override;
    void visit(const FUNCTION& node) override;
    void visit(const POW& node) override;
    void visit(const OR& node) override;
    void visit(const XOR& node) override;
    void visit(const AND& node) override;
    void visit(const SHL& node) override;
    void visit(const SHR& node) override;
    void visit(const ADD& node) override;
    void visit(const MINUS& node) override;
    void visit(const MUL& node) override;
    void visit(const DIV& node) override;
    void visit(const MOD& node) override;
    void visit(const UnaryMINUS& node) override;
    void visit(const UnaryPLUS& node) override;
    void visit(const UnaryCOMP& node) override;

    private:
    template<typename ast, const char* op>
    requires std::derived_from<ast, BinaryAST>
    void visitBinaryAST(const ast& node);

    template<typename ast, const char* op>
    requires std::derived_from<ast, UnaryAST>
    void visitUnaryAST(const ast& node);
};

} // namespace evaluate

