#pragma once

#include "util/Code.hpp"
#include "AST.hpp"
#include "parse/NodeVisitor.hpp"
#include <memory>
#include <concepts>

namespace evaluate {

class Analyzer : public NodeVisitor {
    private:
    const Code& code;
    std::unique_ptr<AST> reg;

    public:
    explicit Analyzer(const Code& code);

    std::unique_ptr<AST> analyze();

    void visit(const GenericToken& node) override;
    void visit(const Literal& node) override;
    void visit(const Function& node) override;
    void visit(const Primary& node) override;


    void visit(const Unary& node) override;
    void visit(const Pow& node) override;
    void visit(const Or& node) override;
    void visit(const Xor& node) override;
    void visit(const And& node) override;
    void visit(const Shift& node) override;
    void visit(const Additive& node) override;
    void visit(const Multiplicative& node) override;

    private:
    template<typename node, typename ast>
    requires std::derived_from<node, Node> && std::derived_from<ast, AST>
    void visitBinary1(const node& n);
};

} // namespace evaluate
