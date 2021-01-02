#pragma once

#include "Node.hpp"
#include "lex/Lexer.hpp"
#include <concepts>
#include <memory>
#include <optional>

namespace evaluate {

    class Parser {
    private:
        const Code& code;
        Lexer lexer;
        std::optional<Token> reg;

    public:
        explicit Parser(const Code& code);
        std::unique_ptr<Node> parse();

    private:
        Token next();

        std::unique_ptr<Node> parseLiteral();
        std::unique_ptr<Node> parseFunction();
        std::unique_ptr<Node> parsePrimary();
        std::unique_ptr<Node> parseUnary();

        template <typename node>
        requires std::derived_from<node, OptionalExpression<typename node::child_type>>
            || std::same_as<node, Unary>
        std::unique_ptr<Node> parseOptionalList();
    };

} // namespace evaluate

