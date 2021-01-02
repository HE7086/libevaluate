#include "Parser.hpp"
#include "Node.hpp"
#include "util/Error.hpp"
#include <cerrno>
#include <charconv>
#include <cstdlib>

using namespace std;

namespace evaluate {

Parser::Parser(const Code& code) : code(code), lexer(code) {}

unique_ptr<Node> Parser::parse() { return parseOptionalList<Pow>(); }

Token Parser::next() {
    if (reg.has_value()) {
        Token t = move(reg.value());
        // TODO: reset necessary?
        reg.reset();
        return t;
    }
    if (!lexer.nasNext()) {
        error("Syntax Error: no more tokens");
    } else {
        return lexer.next();
    }
}

unique_ptr<Node> Parser::parseLiteral() {
    Token token = next();
    if (token.getType() == Token::Type::NUMBER) {
        if (any_of(token.getCode().begin(), token.getCode().end(),
                   [](char c) { return c == '.'; })) {
            // TODO: wait for gcc11
            // double valueD;
            // auto resultD = from_chars(token.getCode().begin(), token.getCode().end(), valueD);
            string str = string(token.getCode());
            char* end;
            double valueD = strtod(str.c_str(), &end);
            if (errno == ERANGE) {
                error(token.getCodeRef().getFrom(), token.getCode().size(), code,
                      "Syntax Error: floating point value out of range");
            }
            return make_unique<Literal>(token.getCodeRef(), valueD);
        } else {
            int64_t valueI;
            auto resultI = from_chars(token.getCode().begin(), token.getCode().end(), valueI);
            if (resultI.ec == errc::invalid_argument) {
                error(token.getCodeRef().getFrom(), token.getCode().size(), code,
                      "Syntax Error: invalid literal");
            } else if (resultI.ec == errc::result_out_of_range) {
                error(token.getCodeRef().getFrom(), token.getCode().size(), code,
                      "Syntax Error: value out of range");
            } else {
                return make_unique<Literal>(token.getCodeRef(), valueI);
            }
        }
    } else {
        error(token.getCodeRef().getFrom(), token.getCode().size(), code,
              "Syntax Error: unexpected Token, should be: Number");
    }
}

unique_ptr<Node> Parser::parseFunction() {
    Token token = next();
    if (token.getType() == Token::Type::FUNCTION) {
        string_view name = token.getCode();
        Token l = next();
        if (l.getType() != Token::Type::LEFT_BRACKET) {
            error(l.getCodeRef().getFrom(), token.getCode().size(), code,
                  "Syntax Error: unexpected Token, should be: left bracket");
        }
        vector<unique_ptr<Node>> params{};
        while (lexer.nasNext()) {
            Token t = next();
            switch (t.getType()) {
                case Token::Type::RIGHT_BRACKET: {
                    return make_unique<Function>(
                        CodeReference::combine(token.getCodeRef(), t.getCodeRef()), name,
                        make_unique<GenericToken>(l.getCodeRef(), Token::Type::LEFT_BRACKET),
                        move(params),
                        make_unique<GenericToken>(t.getCodeRef(), Token::Type::RIGHT_BRACKET));
                }
                case Token::Type::COMMA: {
                    reg.emplace(t);
                    params.emplace_back(
                        make_unique<GenericToken>(t.getCodeRef(), Token::Type::COMMA));
                    params.emplace_back(parseOptionalList<Pow>());
                    break;
                }
                default: {
                    reg.emplace(t);
                    params.emplace_back(parseOptionalList<Pow>());
                    break;
                }
            }
        }
    } else {
        error(token.getCodeRef().getFrom(), token.getCode().size(), code,
              "Syntax Error: unexpected Token, should be: Function name");
    }
    error(lexer.getOffset(), 1, code, "Syntax Error: unexpected Token, should be: right bracket");
}

unique_ptr<Node> Parser::parsePrimary() {
    Token token = next();
    switch (token.getType()) {
        case Token::Type::NUMBER: {
            reg.emplace(token);
            auto literal = parseLiteral();
            return make_unique<Primary>(literal->getCodeRef(), move(literal));
        }
        case Token::Type::LEFT_BRACKET: {
            auto pow = parseOptionalList<Pow>();
            Token r = next();
            return make_unique<Primary>(
                CodeReference::combine(token.getCodeRef(), r.getCodeRef()),
                make_unique<GenericToken>(token.getCodeRef(), Token::Type::LEFT_BRACKET),
                move(pow),
                make_unique<GenericToken>(token.getCodeRef(), Token::Type::RIGHT_BRACKET));
        }
        case Token::Type::FUNCTION: {
            reg.emplace(token);
            return parseFunction();
        }
        default: {
            error(token.getCodeRef().getFrom(), token.getCode().size(), code,
                  "Syntax Error: unexpected Token, should be: primary expression");
        }
    }
}

unique_ptr<Node> Parser::parseUnary() {
    Token token = next();
    switch (token.getType()) {
        case Token::Type::PLUS:
        case Token::Type::MINUS:
        case Token::Type::COMP: {
            auto exp = parseUnary();
            return make_unique<Unary>(CodeReference::combine(token.getCodeRef(), exp->getCodeRef()),
                                      make_unique<GenericToken>(token.getCodeRef(),
                                                                token.getType()),
                                      move(exp));
        }
        default: {
            reg.emplace(token);
            return parsePrimary();
        }
    }
}

template <typename node>
    requires derived_from<node, OptionalExpression<typename node::child_type>> ||
    std::same_as<node, Unary> unique_ptr<Node> Parser::parseOptionalList() {
    auto l_expr = parseOptionalList<typename node::child_type>();
    if (reg.has_value() || lexer.nasNext()) {
        Token token = next();
        if (node::isValidOperation(token.getType())) {
            auto r_expr = parseOptionalList<node>();
            return make_unique<node>(CodeReference::combine(l_expr->getCodeRef(),
                                                            r_expr->getCodeRef()),
                                     move(l_expr),
                                     make_unique<GenericToken>(token.getCodeRef(), token.getType()),
                                     move(r_expr));
        } else {
            reg.template emplace(token);
        }
    }
    return l_expr;
}

template <> unique_ptr<Node> Parser::parseOptionalList<Unary>() { return parseUnary(); }

} // namespace evaluate