#pragma once

#include "analyze/ASTVisitor.hpp"
#include "util/Code.hpp"
#include <cstdint>
#include <ostream>
#include <string>
#include <variant>

namespace evaluate {
class VALUE;
class FUNCTION;
class POW;
class OR;
class XOR;
class AND;
class SHL;
class SHR;
class ADD;
class MINUS;
class MUL;
class DIV;
class MOD;
class UnaryMINUS;
class UnaryPLUS;
class UnaryCOMP;

class Evaluator : private ASTVisitor {
    private:
    Code code;
    std::variant<int64_t, double> value;

    public:
    explicit Evaluator(std::string expr);
    std::variant<int64_t, double> get();

    private:
    void visit(const VALUE& node) override;
    void visit(const FUNCTION& node) override;
    void visit(const POW& node) override;
    void visit(const OR& node) override;
    void visit(const XOR& node) override;
    void visit(const AND& node) override;
    void visit(const SHL& node) override;
    void visit(const SHR& node) override;
    void visit(const ADD& node) override;
    void visit(const MINUS& node) override;
    void visit(const MUL& node) override;
    void visit(const DIV& node) override;
    void visit(const MOD& node) override;
    void visit(const UnaryMINUS& node) override;
    void visit(const UnaryPLUS& node) override;
    void visit(const UnaryCOMP& node) override;
};

} // namespace evaluate

[[maybe_unused]] static int64_t evall(std::string expr) {
    return get<int64_t>(evaluate::Evaluator(move(expr)).get());
}
[[maybe_unused]] static double evalf(std::string expr) {
    return get<double>(evaluate::Evaluator(move(expr)).get());
}
[[maybe_unused]] static std::variant<int64_t, double> eval(std::string expr) {
    return evaluate::Evaluator(move(expr)).get();
}

inline std::ostream& operator<<(std::ostream& os, const std::variant<int64_t, double> value) {
    os << (std::holds_alternative<double>(value) ? std::get<double>(value) :
                                                   std::get<int64_t>(value));
    return os;
}