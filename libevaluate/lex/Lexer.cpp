#include "Lexer.hpp"
#include "util/Error.hpp"
#include <cctype>

using namespace std;

namespace evaluate {

    Lexer::Lexer(const Code& code) : code(code) {}

    static bool isFunction(char c) {
        return isalnum(c) || c == '_';
    }

    Token Lexer::next() {
        const size_t size = code.size();
        while(offset < size) {
            char c = code.charAt(offset);
            if (isspace(c)) {
                ++offset;
                continue;
            } else if (isdigit(c) || c == '.') {
                size_t start = offset;
                while (offset < size) {
                    c = code.charAt(++offset);
                    if (!isdigit(c) && c != '.') {
                        break;
                    }
                }
                return {Token::Type::NUMBER, code.ref(start, offset)};
            } else if (isalpha(c)) { // start with a alphabet
                size_t start = offset;
                while (offset < size && isFunction(code.charAt(++offset)));
                return {Token::Type::FUNCTION, code.ref(start, offset)};
            } else {
                ++offset;
                switch (c) {
                    case ',': { return {Token::Type::COMMA, code.ref(offset - 1, offset)}; }
                    case '+': { return {Token::Type::PLUS, code.ref(offset - 1, offset)}; }
                    case '-': { return {Token::Type::MINUS, code.ref(offset - 1, offset)}; }
                    case '/': { return {Token::Type::DIV, code.ref(offset - 1, offset)}; }
                    case '%': { return {Token::Type::MOD, code.ref(offset - 1, offset)}; }
                    case '&': { return {Token::Type::AND, code.ref(offset - 1, offset)}; }
                    case '|': { return {Token::Type::OR, code.ref(offset - 1, offset)}; }
                    case '~': { return {Token::Type::COMP, code.ref(offset - 1, offset)}; }
                    case '^': { return {Token::Type::XOR, code.ref(offset - 1, offset)}; }
                    case '(': { return {Token::Type::LEFT_BRACKET, code.ref(offset - 1, offset)}; }
                    case ')': { return {Token::Type::RIGHT_BRACKET, code.ref(offset - 1, offset)}; }
                    case '*': {
                        if (offset < size && code.charAt(offset) == '*') {
                            ++offset;
                            return {Token::Type::POWER, code.ref(offset - 2, offset)};
                        } else {
                            return {Token::Type::MUL, code.ref(offset - 1, offset)};
                        }
                    }
                    case '<': {
                        if (offset < size && code.charAt(offset) == '<') {
                            ++offset;
                            return {Token::Type::SHL, code.ref(offset - 2, offset)};
                        } else {
                            error(offset - 1, 2, code, "unexpected character, should be: <<");
                        }
                    }
                    case '>': {
                        if (offset < size && code.charAt(offset) == '>') {
                            ++offset;
                            return {Token::Type::SHR, code.ref(offset - 2, offset)};
                        } else {
                            error(offset - 1, 2, code, "unexpected character, should be: >>");
                        }
                    }
                    default: {
                        error(offset - 1, 1, code, "unknown character");
                    }
                }
            }
        }
        error(offset, 1, code, "unknown error: out of bound");
    }

    bool Lexer::nasNext() const {
        return offset < code.size();
    }

    size_t Lexer::getOffset() const {
        return offset;
    }
} // namespace evaluate

