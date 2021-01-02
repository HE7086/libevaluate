#pragma once

#include "lex/Token.hpp"
#include "util/Code.hpp"
#include <cstdint>
#include <memory>
#include <string_view>
#include <variant>
#include <vector>

namespace evaluate {

class NodeVisitor;

class Node {
    public:
    enum class Type {
        GenericToken,
        Literal,
        Function,
        Primary,
        Unary,
        Pow,
        Or,
        Xor,
        And,
        Shift,
        Additive,
        Multiplicative,
    };

    private:
    const Node::Type type;
    const CodeReference codeRef;

    public:
    Node(Node::Type type, CodeReference codeRef);
    virtual ~Node() noexcept = default;

    virtual void accept(NodeVisitor& visitor) const = 0;

    std::string_view getCode() const;
    CodeReference getCodeRef() const;
    Node::Type getType() const;
};

class GenericToken : public Node {
    private:
    Token::Type tokenType;

    public:
    GenericToken(CodeReference codeRef, Token::Type tokenType);
    void accept(NodeVisitor& visitor) const override;
    Token::Type getTokenType() const;
};

class Literal : public Node {
    private:
    std::variant<int64_t, double> value;

    public:
    Literal(CodeReference codeRef, int64_t value);

    Literal(CodeReference codeRef, double value);

    void accept(NodeVisitor& visitor) const override;
    std::variant<int64_t, double> getValue() const;
    double asDouble() const;
    int64_t asInt() const;
    bool isFP() const;
};

class Function : public Node {
    private:
    std::string_view name;
    std::unique_ptr<Node> l;
    std::vector<std::unique_ptr<Node>> parameters;
    std::unique_ptr<Node> r;

    public:
    Function(CodeReference codeRef, std::string_view name, std::unique_ptr<Node> l,
             std::vector<std::unique_ptr<Node>>&& parameters, std::unique_ptr<Node> r);
    void accept(NodeVisitor& visitor) const override;

    std::string_view getName() const;
    GenericToken& getL() const;
    const std::vector<std::unique_ptr<Node>>& getParameters() const;
    GenericToken& getR() const;
};

class Primary : public Node {
    private:
    std::unique_ptr<Node> l;
    std::unique_ptr<Node> child;
    std::unique_ptr<Node> r;

    public:
    Primary(CodeReference codeRef, std::unique_ptr<Node> child);

    Primary(CodeReference codeRef, std::unique_ptr<GenericToken> l, std::unique_ptr<Node> child,
            std::unique_ptr<GenericToken> r);

    void accept(NodeVisitor& visitor) const override;
    bool hasLR() const;
    Node& getL() const;
    Node& getChild() const;
    Node& getR() const;
};

class Unary : public Node {
    private:
    std::unique_ptr<Node> option; // optional
    std::unique_ptr<Node> expression;

    public:
    Unary(CodeReference codeRef, std::unique_ptr<Node> op, std::unique_ptr<Node> expression);

    Unary(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    bool hasOption() const;
    Node& getOption() const;
    Node& getExpression() const;
};

template <typename child> class OptionalExpression : public Node {
    protected:
    std::unique_ptr<Node> expression;
    std::unique_ptr<Node> operation; // optional
    std::unique_ptr<Node> next_exp; // optional

    public:
    using child_type = child;

    OptionalExpression(Node::Type type, CodeReference codeRef, std::unique_ptr<Node> expression,
                       std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp)
        : Node(type, codeRef), expression(move(expression)), operation(move(operation)),
          next_exp(move(next_exp)) {}

    OptionalExpression(Node::Type type, CodeReference codeRef, std::unique_ptr<Node> expression)
        : Node(type, codeRef), expression(move(expression)), operation(nullptr), next_exp(nullptr) {
    }

    bool hasOptional() const { return operation && next_exp; }
    Node& getExpression() const { return *expression; }
    Node& getOperation() const { return *operation; }
    Node& getNext() const { return *next_exp; }
};

class Multiplicative : public OptionalExpression<Unary> {
    public:
    Multiplicative(CodeReference codeRef, std::unique_ptr<Node> expression,
                   std::unique_ptr<Node> operation,
                   std::unique_ptr<Node> next_exp);

    Multiplicative(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) {
        return type == Token::Type::MUL || type == Token::Type::DIV || type == Token::Type::MOD;
    }
};

class Additive : public OptionalExpression<Multiplicative> {
    public:
    Additive(CodeReference codeRef, std::unique_ptr<Node> expression,
             std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    Additive(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) {
        return type == Token::Type::PLUS || type == Token::Type::MINUS;
    }
};

class Shift : public OptionalExpression<Additive> {
    public:
    Shift(CodeReference codeRef, std::unique_ptr<Node> expression,
          std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    Shift(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) {
        return type == Token::Type::SHL || type == Token::Type::SHR;
    }
};

class And : public OptionalExpression<Shift> {
    public:
    And(CodeReference codeRef, std::unique_ptr<Node> expression,
        std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    And(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) { return type == Token::Type::AND; }
};

class Xor : public OptionalExpression<And> {
    public:
    Xor(CodeReference codeRef, std::unique_ptr<Node> expression,
        std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    Xor(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) { return type == Token::Type::XOR; }
};

class Or : public OptionalExpression<Xor> {
    public:
    Or(CodeReference codeRef, std::unique_ptr<Node> expression,
       std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    Or(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) { return type == Token::Type::OR; }
};

class Pow : public OptionalExpression<Or> {
    public:
    Pow(CodeReference codeRef, std::unique_ptr<Node> expression,
        std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp);

    Pow(CodeReference codeRef, std::unique_ptr<Node> expression);

    void accept(NodeVisitor& visitor) const override;
    static constexpr bool isValidOperation(Token::Type type) { return type == Token::Type::POWER; }
};

} // namespace evaluate
