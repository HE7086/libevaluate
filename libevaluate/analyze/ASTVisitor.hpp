#pragma once

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

class ASTVisitor {
    public:
    virtual void visit(const VALUE& node) = 0;
    virtual void visit(const FUNCTION& node) = 0;
    virtual void visit(const POW& node) = 0;
    virtual void visit(const OR& node) = 0;
    virtual void visit(const XOR& node) = 0;
    virtual void visit(const AND& node) = 0;
    virtual void visit(const SHL& node) = 0;
    virtual void visit(const SHR& node) = 0;
    virtual void visit(const ADD& node) = 0;
    virtual void visit(const MINUS& node) = 0;
    virtual void visit(const MUL& node) = 0;
    virtual void visit(const DIV& node) = 0;
    virtual void visit(const MOD& node) = 0;
    virtual void visit(const UnaryMINUS& node) = 0;
    virtual void visit(const UnaryPLUS& node) = 0;
    virtual void visit(const UnaryCOMP& node) = 0;
};

} // namespace evaluate