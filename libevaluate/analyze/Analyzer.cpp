#include "Analyzer.hpp"
#include "Functions.hpp"
#include "parse/Parser.hpp"
#include "util/Error.hpp"
#include <cassert>
#include <unordered_map>

using namespace std;

namespace evaluate {

Analyzer::Analyzer(const Code& code) : code(code) {}

unique_ptr<AST> Analyzer::analyze() {
    Parser parser(code);
    auto node = parser.parse();
    node->accept(*this);
    return move(reg);
}
void Analyzer::visit(const GenericToken&) { __builtin_unreachable(); }
void Analyzer::visit(const Literal& node) {
    reg = make_unique<VALUE>(node.getCodeRef(), node.isFP() ? node.asDouble() : node.asInt());
}
void Analyzer::visit(const Function& node) {
    const auto type = functionNames.find(string(node.getName()));
    if (type == functionNames.end()) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Semantic Error: unknown function name");
    } else {
        vector<unique_ptr<AST>> parameters{};
        for (auto& ptr : node.getParameters()) {
            if (ptr->getType() == Node::Type::GenericToken) {
                continue;
            }
            ptr->accept(*this);
            parameters.emplace_back(move(reg));
        }
        reg = make_unique<FUNCTION>(node.getCodeRef(), type->second, node.getName(),
                                    move(parameters));
    }
}
void Analyzer::visit(const Primary& node) { node.getChild().accept(*this); }
void Analyzer::visit(const Unary& node) {
    node.getExpression().accept(*this);
    if (node.hasOption()) {
        switch (static_cast<GenericToken&>(node.getOption()).getTokenType()) {
            case Token::Type::PLUS: {
                reg = make_unique<UnaryPLUS>(node.getCodeRef(), move(reg));
                break;
            }
            case Token::Type::MINUS: {
                reg = make_unique<UnaryMINUS>(node.getCodeRef(), move(reg));
                break;
            }
            case Token::Type::COMP: {
                reg = make_unique<UnaryCOMP>(node.getCodeRef(), move(reg));
                break;
            }
            default:
                error(node.getOption().getCodeRef().getFrom(), node.getOption().getCode().size(),
                      code, "Semantic Error: unknown unary operator");
        }
    }
}
template <typename node, typename ast>
requires std::derived_from<node, Node>&& std::derived_from<ast, AST> void
Analyzer::visitBinary1(const node& n) {
    n.getExpression().accept(*this);
    if (n.hasOptional()) {
        assert(node::isValidOperation(static_cast<GenericToken&>(n.getOperation()).getTokenType()));
        auto l_expr = move(reg);
        n.getNext().accept(*this);
        reg = make_unique<ast>(n.getCodeRef(), move(l_expr), move(reg));
    }
}
void Analyzer::visit(const Pow& node) { visitBinary1<Pow, POW>(node); }
void Analyzer::visit(const Or& node) { visitBinary1<Or, OR>(node); }
void Analyzer::visit(const Xor& node) { visitBinary1<Xor, XOR>(node); }
void Analyzer::visit(const And& node) { visitBinary1<And, AND>(node); }
void Analyzer::visit(const Shift& node) {
    node.getExpression().accept(*this);
    if (node.hasOptional()) {
        auto l_expr = move(reg);
        node.getNext().accept(*this);
        switch (static_cast<GenericToken&>(node.getOperation()).getTokenType()) {
            case Token::Type::SHL: {
                reg = make_unique<SHL>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            case Token::Type::SHR: {
                reg = make_unique<SHR>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            default: {
                error(node.getOperation().getCodeRef().getFrom(),
                      node.getOperation().getCode().size(), code,
                      "Semantic Error: unknown operator");
            }
        }
    }
}
void Analyzer::visit(const Additive& node) {
    node.getExpression().accept(*this);
    if (node.hasOptional()) {
        auto l_expr = move(reg);
        node.getNext().accept(*this);
        switch (static_cast<GenericToken&>(node.getOperation()).getTokenType()) {
            case Token::Type::PLUS: {
                reg = make_unique<ADD>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            case Token::Type::MINUS: {
                reg = make_unique<MINUS>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            default: {
                error(node.getOperation().getCodeRef().getFrom(),
                      node.getOperation().getCode().size(), code,
                      "Semantic Error: unknown operator");
            }
        }
    }
}
void Analyzer::visit(const Multiplicative& node) {
    node.getExpression().accept(*this);
    if (node.hasOptional()) {
        auto l_expr = move(reg);
        node.getNext().accept(*this);
        switch (static_cast<GenericToken&>(node.getOperation()).getTokenType()) {
            case Token::Type::MUL: {
                reg = make_unique<MUL>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            case Token::Type::DIV: {
                reg = make_unique<DIV>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            case Token::Type::MOD: {
                reg = make_unique<MOD>(node.getCodeRef(), move(l_expr), move(reg));
                break;
            }
            default: {
                error(node.getOperation().getCodeRef().getFrom(),
                      node.getOperation().getCode().size(), code,
                      "Semantic Error: unknown operator");
            }
        }
    }
}
} // namespace evaluate