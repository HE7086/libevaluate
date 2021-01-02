#pragma once

#include "Token.hpp"

namespace evaluate {

    class Lexer {
    private:
        size_t offset = 0;
        const Code &code;

    public:
        explicit Lexer(const Code &code);

        Token next();

        bool nasNext() const;

        size_t getOffset() const;

    };

} // namespace evaluate



