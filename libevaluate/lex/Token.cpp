#include "Token.hpp"

#include <utility>

namespace evaluate {

    Token::Token(Token::Type type, CodeReference code) : type(type), codeRef(std::move(code)) {}

    Token::Type Token::getType() const {
        return type;
    }

    std::string_view Token::getCode() const {
        return codeRef.str();
    }

    CodeReference Token::getCodeRef() const {
        return codeRef;
    }
} // namespace evaluate

