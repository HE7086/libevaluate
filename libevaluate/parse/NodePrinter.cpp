#include "NodePrinter.hpp"
#include "Node.hpp"
#include <iostream>

using namespace std;

namespace evaluate {

NodePrinter::NodePrinter(const Code& code) : code(code) {}

void NodePrinter::visit(const GenericToken& node) {
    cout << count << " [label=\"Generic: " << node.getCode() << "\"]" << endl;
}

void NodePrinter::visit(const Literal& node) {
    cout << count << " [label=\"Literal: " << node.getCode() << "\"]" << endl;
}

void NodePrinter::visit(const Function& node) {
    size_t id = count;
    cout << count << " [label=\"Function: " << node.getName() << "\"]" << endl;
    cout << id << " -> " << ++count << endl;
    node.getL().accept(*this);
    for(auto& n: node.getParameters()) {
        cout << id << " -> " << ++count << endl;
        n->accept(*this);
    }
    cout << id << " -> " << ++count << endl;
    node.getR().accept(*this);
}

void NodePrinter::visit(const Primary& node) {
    size_t id = count;
    cout << count << " [label=\"Primary\"]" << endl;
    if (node.hasLR()) {
        cout << id << " -> " << ++count << endl;
        node.getL().accept(*this);
    }
    cout << id << " -> " << ++count << endl;
    node.getChild().accept(*this);
    if (node.hasLR()) {
        cout << id << " -> " << ++count << endl;
        node.getR().accept(*this);
    }
}

void NodePrinter::visit(const Unary& node) {
    size_t id = count;
    cout << count << " [label=\"Unary\"]" << endl;
    if (node.hasOption()) {
        cout << id << " -> " << ++count << endl;
        node.getOption().accept(*this);
    }
    cout << id << " -> " << ++count << endl;
    node.getExpression().accept(*this);
}

template <typename OpExpr, const char* name>
void NodePrinter::visit(const OpExpr& node) {
    size_t id = count;
    cout << count << " [label=\"" << name << "\"]" << endl;
    cout << id << " -> " << ++count << endl;
    node.getExpression().accept(*this);
    if (node.hasOptional()) {
        cout << id << " -> " << ++count << endl;
        node.getOperation().accept(*this);
        cout << id << " -> " << ++count << endl;
        node.getNext().accept(*this);
    }
}

void NodePrinter::visit(const Pow& node) {
    // dirty hack
    static constexpr const char name[] = "Pow";
    visit<Pow, name>(node);
}

void NodePrinter::visit(const Or& node) {
    // dirty hack
    static constexpr const char name[] = "Or";
    visit<Or, name>(node);
}

void NodePrinter::visit(const Xor& node) {
    // dirty hack
    static constexpr const char name[] = "Xor";
    visit<Xor, name>(node);
}

void NodePrinter::visit(const And& node) {
    // dirty hack
    static constexpr const char name[] = "And";
    visit<And, name>(node);
}

void NodePrinter::visit(const Shift& node) {
    // dirty hack
    static constexpr const char name[] = "Shift";
    visit<Shift, name>(node);
}

void NodePrinter::visit(const Additive& node) {
    // dirty hack
    static constexpr const char name[] = "Additive";
    visit<Additive, name>(node);
}

void NodePrinter::visit(const Multiplicative& node) {
    // dirty hack
    static constexpr const char name[] = "Multiplicative";
    visit<Multiplicative, name>(node);
}

} // namespace evaluate
