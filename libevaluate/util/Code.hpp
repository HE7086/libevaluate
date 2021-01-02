#pragma once

#include <string>
#include <string_view>
#include "Error.hpp"


namespace evaluate {

    class CodeReference {
    private:
        const size_t from;
        const size_t to;
        const std::string_view code;

    public:
        CodeReference(size_t from, size_t to, std::string_view code);

        size_t getFrom() const;
        size_t getTo() const;
        std::string_view str() const;

        static CodeReference combine(const CodeReference& a, const CodeReference& b);
    };

    class Code {
    private:
        const std::string code;

    public:
        Code(std::string code);

        char charAt(size_t index) const;
        std::string_view substr(size_t from, size_t to) const;
        std::string_view str() const;
        CodeReference ref(size_t from, size_t to) const;
        size_t size() const;

    };

} // namespace evaluate

