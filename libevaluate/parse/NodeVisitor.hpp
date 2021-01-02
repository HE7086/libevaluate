#pragma once

namespace evaluate {
    class GenericToken;
    class Literal;
    class Function;
    class Primary;
    class Unary;
    class Pow;
    class Or;
    class Xor;
    class And;
    class Shift;
    class Additive;
    class Multiplicative;

    class NodeVisitor {
    public:
        virtual ~NodeVisitor() noexcept = default;
        virtual void visit(const GenericToken& node) = 0;
        virtual void visit(const Literal& node) = 0;
        virtual void visit(const Function& node) = 0;
        virtual void visit(const Primary& node) = 0;
        virtual void visit(const Unary& node) = 0;
        virtual void visit(const Pow& node) = 0;
        virtual void visit(const Or& node) = 0;
        virtual void visit(const Xor& node) = 0;
        virtual void visit(const And& node) = 0;
        virtual void visit(const Shift& node) = 0;
        virtual void visit(const Additive& node) = 0;
        virtual void visit(const Multiplicative& node) = 0;
    };

} // namespace evaluate