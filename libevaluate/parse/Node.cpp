#include "Node.hpp"
#include "NodeVisitor.hpp"

using namespace std;

namespace evaluate {

Node::Node(Node::Type type, CodeReference codeRef) : type(type), codeRef(move(codeRef)) {}

string_view Node::getCode() const { return codeRef.str(); }

Node::Type Node::getType() const { return type; }

CodeReference Node::getCodeRef() const { return codeRef; }

GenericToken::GenericToken(CodeReference codeRef, Token::Type tokenType)
    : Node(Node::Type::GenericToken, codeRef), tokenType(tokenType) {}
void GenericToken::accept(NodeVisitor& visitor) const { visitor.visit(*this); }
Token::Type GenericToken::getTokenType() const { return tokenType; }

Literal::Literal(CodeReference codeRef, int64_t value)
    : Node(Node::Type::Literal, codeRef), value(value) {}

Literal::Literal(CodeReference codeRef, double value)
    : Node(Node::Type::Literal, codeRef), value(value) {}

bool Literal::isFP() const { return holds_alternative<double>(value); }
std::variant<int64_t, double> Literal::getValue() const { return value; }
void Literal::accept(NodeVisitor& visitor) const { visitor.visit(*this); }
double Literal::asDouble() const { return get<double>(value); }
int64_t Literal::asInt() const { return get<int64_t>(value); }

Function::Function(CodeReference codeRef, std::string_view name, std::unique_ptr<Node> l,
                   std::vector<std::unique_ptr<Node>>&& parameters, std::unique_ptr<Node> r)
    : Node(Node::Type::Function, codeRef), name(name), l(move(l)), parameters(move(parameters)),
      r(move(r)) {}
string_view Function::getName() const { return name; }
GenericToken& Function::getL() const { return static_cast<GenericToken&>(*l); }
const vector<std::unique_ptr<Node>>& Function::getParameters() const { return parameters; }
GenericToken& Function::getR() const { return static_cast<GenericToken&>(*r); }
void Function::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Primary::Primary(CodeReference codeRef, unique_ptr<Node> child)
    : Node(Node::Type::Primary, codeRef), l(nullptr), child(move(child)), r(nullptr) {}

Primary::Primary(CodeReference codeRef, std::unique_ptr<GenericToken> l,
                 std::unique_ptr<Node> child, std::unique_ptr<GenericToken> r)
    : Node(Node::Type::Primary, codeRef), l(move(l)), child(move(child)), r(move(r)) {}
Node& Primary::getL() const { return *l; }
Node& Primary::getChild() const { return *child; }
Node& Primary::getR() const { return *r; }
void Primary::accept(NodeVisitor& visitor) const { visitor.visit(*this); }
bool Primary::hasLR() const { return l && r; }

Unary::Unary(CodeReference codeRef, unique_ptr<Node> option, unique_ptr<Node> expression)
    : Node(Node::Type::Unary, codeRef), option(move(option)), expression(move(expression)) {}

Unary::Unary(CodeReference codeRef, unique_ptr<Node> expression)
    : Node(Node::Type::Unary, codeRef), option(nullptr), expression(move(expression)) {}
Node& Unary::getOption() const { return *option; }
Node& Unary::getExpression() const { return *expression; }
void Unary::accept(NodeVisitor& visitor) const { visitor.visit(*this); }
bool Unary::hasOption() const { return option.operator bool(); }

Multiplicative::Multiplicative(CodeReference codeRef, unique_ptr<Node> expression,
                               std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Multiplicative, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Multiplicative::Multiplicative(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Multiplicative, codeRef, move(expression)) {}
void Multiplicative::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Additive::Additive(CodeReference codeRef, unique_ptr<Node> expression,
                   std::unique_ptr<Node> operation, std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Additive, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Additive::Additive(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Additive, codeRef, move(expression)) {}
void Additive::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Shift::Shift(CodeReference codeRef, unique_ptr<Node> expression, std::unique_ptr<Node> operation,
             std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Shift, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Shift::Shift(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Shift, codeRef, move(expression)) {}
void Shift::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

And::And(CodeReference codeRef, unique_ptr<Node> expression, std::unique_ptr<Node> operation,
         std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::And, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
And::And(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::And, codeRef, move(expression)) {}
void And::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Xor::Xor(CodeReference codeRef, unique_ptr<Node> expression, std::unique_ptr<Node> operation,
         std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Xor, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Xor::Xor(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Xor, codeRef, move(expression)) {}
void Xor::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Or::Or(CodeReference codeRef, unique_ptr<Node> expression, std::unique_ptr<Node> operation,
       std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Or, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Or::Or(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Or, codeRef, move(expression)) {}
void Or::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

Pow::Pow(CodeReference codeRef, unique_ptr<Node> expression, std::unique_ptr<Node> operation,
         std::unique_ptr<Node> next_exp)
    : OptionalExpression(Node::Type::Pow, codeRef, move(expression), move(operation),
                         move(next_exp)) {}
Pow::Pow(CodeReference codeRef, unique_ptr<Node> expression)
    : OptionalExpression(Node::Type::Pow, codeRef, move(expression)) {}
void Pow::accept(NodeVisitor& visitor) const { visitor.visit(*this); }

} // namespace evaluate
