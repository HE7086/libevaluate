#include "ASTPrinter.hpp"
#include "AST.hpp"
#include <iostream>

using namespace std;

namespace evaluate {

ASTPrinter::ASTPrinter(const Code& code) : code(code) {}

void ASTPrinter::visit(const VALUE& node) {
    cout << count << " [label=\"" << (node.isFP() ? node.asDouble() : node.asInt())
         << (node.isFP() ? 'd' : 'i') << "\"]" << endl;
}
void ASTPrinter::visit(const FUNCTION& node) {
    size_t id = count;
    cout << count << " [label=\"" << node.getName() << "\"]" << endl;
    for (auto& param: node.getParameters()) {
        cout << id << " -> " << ++count << endl;
        param->accept(*this);
    }
}
template <typename ast, const char* op>
requires std::derived_from<ast, BinaryAST>
void ASTPrinter::visitBinaryAST(const ast& node) {
    size_t id = count;
    cout << count << " [label=\"" << op << "\"]" << endl;
    node.getLExpr().accept(*this);
    cout << id << " -> " << ++count << endl;
    node.getRExpr().accept(*this);
    cout << id << " -> " << ++count << endl;
}
void ASTPrinter::visit(const POW& node) {
    static const char op[] = "**";
    visitBinaryAST<POW, op>(node);
}
void ASTPrinter::visit(const OR& node) {
    static const char op[] = "|";
    visitBinaryAST<OR, op>(node);
}
void ASTPrinter::visit(const XOR& node) {
    static const char op[] = "^";
    visitBinaryAST<XOR, op>(node);
}
void ASTPrinter::visit(const AND& node) {
    static const char op[] = "&";
    visitBinaryAST<AND, op>(node);
}
void ASTPrinter::visit(const SHL& node) {
    static const char op[] = "<<";
    visitBinaryAST<SHL, op>(node);
}
void ASTPrinter::visit(const SHR& node) {
    static const char op[] = ">>";
    visitBinaryAST<SHR, op>(node);
}
void ASTPrinter::visit(const ADD& node) {
    static const char op[] = "+";
    visitBinaryAST<ADD, op>(node);
}
void ASTPrinter::visit(const MINUS& node) {
    static const char op[] = "-";
    visitBinaryAST<MINUS, op>(node);
}
void ASTPrinter::visit(const MUL& node) {
    static const char op[] = "*";
    visitBinaryAST<MUL, op>(node);
}
void ASTPrinter::visit(const DIV& node) {
    static const char op[] = "/";
    visitBinaryAST<DIV, op>(node);
}
void ASTPrinter::visit(const MOD& node) {
    static const char op[] = "%";
    visitBinaryAST<MOD, op>(node);
}
template <typename ast, const char* op>
requires std::derived_from<ast, UnaryAST>
void ASTPrinter::visitUnaryAST(const ast& node) {
    size_t id = count;
    cout << count << " [label=\"" << op << "\"]" << endl;
    node.getChild().accept(*this);
    cout << id << " -> " << ++count << endl;
}
void ASTPrinter::visit(const UnaryMINUS& node) {
    static const char op[] = "-";
    visitUnaryAST<UnaryMINUS, op>(node);
}
void ASTPrinter::visit(const UnaryPLUS& node) {
    static const char op[] = "+";
    visitUnaryAST<UnaryPLUS, op>(node);
}
void ASTPrinter::visit(const UnaryCOMP& node) {
    static const char op[] = "~";
    visitUnaryAST<UnaryCOMP, op>(node);
}

} // namespace evaluate
