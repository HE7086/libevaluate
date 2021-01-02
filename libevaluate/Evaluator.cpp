#include "Evaluator.hpp"
#include "Functions.hpp"
#include "analyze/Analyzer.hpp"
#include "util/Error.hpp"

#include <cmath>
#include <utility>

using namespace std;

namespace evaluate {

Evaluator::Evaluator(string expr) : code(move(expr)) {}
variant<int64_t, double> Evaluator::get() {
    Analyzer analyzer(code);
    auto result = analyzer.analyze();
    result->accept(*this);
    return value;
}

void Evaluator::visit(const evaluate::VALUE& node) { value = node.getValue(); }
void Evaluator::visit(const evaluate::FUNCTION& node) {
    auto type = node.getFunctionType();
    auto& parameters = node.getParameters();
    vector<variant<int64_t, double>> values{};
    for (auto& p : parameters) {
        p->accept(*this);
        values.emplace_back(value);
    }
    // TODO: optimize this
    value = call(type, values);
}
void Evaluator::visit(const evaluate::POW& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = pow(getAsDouble(v), getAsDouble(value));
    } else {
        value = pow(std::get<int64_t>(v), std::get<int64_t>(value));
    }
}
void Evaluator::visit(const evaluate::OR& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = std::get<int64_t>(v) | std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::XOR& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = std::get<int64_t>(v) ^ std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::AND& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = std::get<int64_t>(v) & std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::SHL& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = std::get<int64_t>(v) << std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::SHR& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = std::get<int64_t>(v) >> std::get<int64_t>(value);
    }
}

void Evaluator::visit(const evaluate::ADD& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = getAsDouble(v) + getAsDouble(value);
    } else {
        value = std::get<int64_t>(v) + std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::MINUS& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = getAsDouble(v) - getAsDouble(value);
    } else {
        value = std::get<int64_t>(v) - std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::MUL& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = getAsDouble(v) * getAsDouble(value);
    } else {
        value = std::get<int64_t>(v) * std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::DIV& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = getAsDouble(v) / getAsDouble(value);
    } else {
        value = std::get<int64_t>(v) / std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::MOD& node) {
    node.getLExpr().accept(*this);
    auto v = value;
    node.getRExpr().accept(*this);
    if (holds_alternative<double>(v) || holds_alternative<double>(value)) {
        value = fmod(getAsDouble(v), getAsDouble(value));
    } else {
        value = std::get<int64_t>(v) % std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::UnaryMINUS& node) {
    node.getChild().accept(*this);
    if (holds_alternative<double>(value)) {
        value = -getAsDouble(value);
    } else {
        value = -std::get<int64_t>(value);
    }
}
void Evaluator::visit(const evaluate::UnaryPLUS& node) { node.getChild().accept(*this); }
void Evaluator::visit(const evaluate::UnaryCOMP& node) {
    node.getChild().accept(*this);
    if (holds_alternative<double>(value)) {
        error(node.getCodeRef().getFrom(), node.getCode().size(), code,
              "Evaluation Error: invalid usage of bitwise operator on double");
    } else {
        value = ~std::get<int64_t>(value);
    }
}

} // namespace evaluate
