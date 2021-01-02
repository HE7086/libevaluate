#include "AST.hpp"

#include "ASTVisitor.hpp"
#include <utility>

using namespace std;

namespace evaluate {

AST::AST(AST::Type type, CodeReference codeRef) : type(type), codeRef(move(codeRef)) {}
std::string_view AST::getCode() const { return codeRef.str(); }
CodeReference AST::getCodeRef() const { return codeRef; }
AST::Type AST::getType() const { return type; }

VALUE::VALUE(CodeReference codeRef, int64_t value) : AST(AST::Type::VALUE, codeRef), value(value) {}
VALUE::VALUE(CodeReference codeRef, double value) : AST(AST::Type::VALUE, codeRef), value(value) {}
void VALUE::accept(ASTVisitor& visitor) const { visitor.visit(*this); }
std::variant<int64_t, double> VALUE::getValue() const { return value; }
bool VALUE::isFP() const { return holds_alternative<double>(value); }
double VALUE::asDouble() const { return get<double>(value); }
int64_t VALUE::asInt() const { return get<int64_t>(value); }

FUNCTION::FUNCTION(CodeReference codeRef, FunctionType functionType, string_view name,
                   std::vector<std::unique_ptr<AST>> parameters)
    : AST(AST::Type::FUNCTION, codeRef), functionType(functionType), name(name),
      parameters(move(parameters)) {}
FunctionType FUNCTION::getFunctionType() const { return functionType; }
const std::vector<std::unique_ptr<AST>>& FUNCTION::getParameters() const { return parameters; }
void FUNCTION::accept(ASTVisitor& visitor) const { visitor.visit(*this); }
std::string_view FUNCTION::getName() const { return name; }

BinaryAST::BinaryAST(AST::Type type, CodeReference codeRef, std::unique_ptr<AST> l_expr,
                     std::unique_ptr<AST> r_expr)
    : AST(type, move(codeRef)), l_expr(move(l_expr)), r_expr(move(r_expr)) {}
const AST& BinaryAST::getLExpr() const { return *l_expr; }
const AST& BinaryAST::getRExpr() const { return *r_expr; }

POW::POW(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::POW, move(codeRef), move(l_expr), move(r_expr)) {}
void POW::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

OR::OR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::OR, move(codeRef), move(l_expr), move(r_expr)) {}
void OR::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

XOR::XOR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::XOR, move(codeRef), move(l_expr), move(r_expr)) {}
void XOR::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

AND::AND(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::AND, move(codeRef), move(l_expr), move(r_expr)) {}
void AND::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

SHL::SHL(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::SHL, move(codeRef), move(l_expr), move(r_expr)) {}
void SHL::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

SHR::SHR(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::SHR, move(codeRef), move(l_expr), move(r_expr)) {}
void SHR::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

ADD::ADD(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::ADD, move(codeRef), move(l_expr), move(r_expr)) {}
void ADD::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

MINUS::MINUS(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::MINUS, move(codeRef), move(l_expr), move(r_expr)) {}
void MINUS::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

MUL::MUL(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::MUL, move(codeRef), move(l_expr), move(r_expr)) {}
void MUL::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

DIV::DIV(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::DIV, move(codeRef), move(l_expr), move(r_expr)) {}
void DIV::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

MOD::MOD(CodeReference codeRef, std::unique_ptr<AST> l_expr, std::unique_ptr<AST> r_expr)
    : BinaryAST(AST::Type::MOD, move(codeRef), move(l_expr), move(r_expr)) {}
void MOD::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

UnaryAST::UnaryAST(AST::Type type, CodeReference codeRef, std::unique_ptr<AST> child)
    : AST(type, move(codeRef)), child(move(child)) {}
const AST& UnaryAST::getChild() const { return *child; }

UnaryMINUS::UnaryMINUS(CodeReference codeRef, std::unique_ptr<AST> child)
    : UnaryAST(AST::Type::UnaryMINUS, codeRef, move(child)) {}
void UnaryMINUS::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

UnaryPLUS::UnaryPLUS(CodeReference codeRef, std::unique_ptr<AST> child)
    : UnaryAST(AST::Type::UnaryPLUS, codeRef, move(child)) {}
void UnaryPLUS::accept(ASTVisitor& visitor) const { visitor.visit(*this); }

UnaryCOMP::UnaryCOMP(CodeReference codeRef, std::unique_ptr<AST> child)
    : UnaryAST(AST::Type::UnaryCOMP, codeRef, move(child)) {}
void UnaryCOMP::accept(ASTVisitor& visitor) const { visitor.visit(*this); }
} // namespace evaluate