#pragma once

#include "util/Code.hpp"

namespace evaluate {

    class Token {
    public:
        enum class Type {
            COMMA,          /* ","  */
            NUMBER,         /* "12" */
            FUNCTION,       /* fun  */
            // arithmetics
            PLUS,           /* "+"  */
            MINUS,          /* "-"  */
            MUL,            /* "*"  */
            DIV,            /* "/"  */
            MOD,            /* "%"  */
            POWER,          /* "**" */
            // binaries
            COMP,           /* "~"  */
            AND,            /* "&"  */
            OR,             /* "|"  */
            XOR,            /* "^"  */
            SHL,            /* "<<" */
            SHR,            /* ">>" */
            // miscellaneous
            LEFT_BRACKET,   /* "("  */
            RIGHT_BRACKET,  /* ")"  */
        };

    private:
        const Type type;
        const CodeReference codeRef;

    public:
        Token(Type type, CodeReference code);

        Type getType() const;
        std::string_view getCode() const;
        CodeReference getCodeRef() const;

    };

} // namespace evaluate

