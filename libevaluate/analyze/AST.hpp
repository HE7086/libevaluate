#pragma once

#include "ASTVisitor.hpp"
#include "Functions.hpp"
#include "parse/Node.hpp"
#include "parse/Parser.hpp"
#include "util/Code.hpp"
#include <memory>
#include <variant>
#include <vector>

namespace evaluate {

class AST {
    public:
    enum class Type {
        VALUE,
        FUNCTION,
        POW,
        OR,
        XOR,
        AND,
        SHL,
        SHR,
        ADD,
        MINUS,
        MUL,
        DIV,
        MOD,
        UnaryMINUS,
        UnaryPLUS,
        UnaryCOMP
    };

    private:
    const AST::Type type;
    const CodeReference codeRef;

    public:
    AST(AST::Type type, CodeReference codeRef);
    virtual ~AST() noexcept = default;

    virtual void accept(ASTVisitor& visitor) const = 0;
    std::string_view getCode() const;
    CodeReference getCodeRef() const;
    AST::Type getType() const;
};

class VALUE : public AST {
    private:
    std::variant<int64_t, double> value;

    public:
    VALUE(CodeReference codeRef, int64_t value);

    VALUE(CodeReference codeRef, double value);

    void accept(ASTVisitor& visitor) const override;
    std::variant<int64_t, double> getValue() const;
    double asDouble() const;
    int64_t asInt() const;
    bool isFP() const;
};
class FUNCTION : public AST {
    private:
    FunctionType functionType;
    std::string_view name;
    std::vector<std::unique_ptr<AST>> parameters;

    public:
    FUNCTION(CodeReference codeRef, FunctionType functionType, std::string_view name,
             std::vector<std::unique_ptr<AST>> parameters);

    void accept(ASTVisitor& visitor) const override;
    std::string_view getName() const;
    FunctionType getFunctionType() const;
    const std::vector<std::unique_ptr<AST>>& getParameters() const;
};

class BinaryAST : public AST {
    protected:
    std::unique_ptr<AST> l_expr;
    std::unique_ptr<AST> r_expr;

    public:
    BinaryAST(AST::Type type, CodeReference codeRef, std::unique_ptr<AST> l_expr,
              std::unique_ptr<AST> r_expr);

    const AST& getLExpr() const;
    const AST& getRExpr() const;
};
class POW : public BinaryAST {
    public:
    POW(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class OR : public BinaryAST {
    public:
    OR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class XOR : public BinaryAST {
    public:
    XOR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class AND : public BinaryAST {
    public:
    AND(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class SHL : public BinaryAST {
    public:
    SHL(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class SHR : public BinaryAST {
    public:
    SHR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class ADD : public BinaryAST {
    public:
    ADD(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class MINUS : public BinaryAST {
    public:
    MINUS(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class MUL : public BinaryAST {
    public:
    MUL(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class DIV : public BinaryAST {
    public:
    DIV(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class MOD : public BinaryAST {
    public:
    MOD(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr);

    void accept(ASTVisitor& visitor) const override;
};
class UnaryAST : public AST {
    protected:
    std::unique_ptr<AST> child;

    public:
    UnaryAST(AST::Type type, CodeReference codeRef, std::unique_ptr<AST> child);

    const AST& getChild() const;
};
class UnaryMINUS : public UnaryAST {
    public:
    UnaryMINUS(CodeReference codeRef, std::unique_ptr<AST> child);

    void accept(ASTVisitor& visitor) const override;
};
class UnaryPLUS : public UnaryAST {
    public:
    UnaryPLUS(CodeReference codeRef, std::unique_ptr<AST> child);

    void accept(ASTVisitor& visitor) const override;
};
class UnaryCOMP : public UnaryAST {
    public:
    UnaryCOMP(CodeReference codeRef, std::unique_ptr<AST> child);

    void accept(ASTVisitor& visitor) const override;
};

} // namespace evaluate
