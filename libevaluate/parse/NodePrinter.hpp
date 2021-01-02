#pragma once

#include "Node.hpp"
#include "NodeVisitor.hpp"
#include <cstddef>

namespace evaluate {
class Code;

class NodePrinter : public NodeVisitor {
    private:
    const Code& code;
    size_t count = 0;

    template<typename OpExpr, const char* name> void visit(const OpExpr& node);

    public:
    explicit NodePrinter(const Code& code);

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
};

} // namespace evaluate
