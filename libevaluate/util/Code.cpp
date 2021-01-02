#include "Code.hpp"

#include <utility>
#include <cassert>

namespace evaluate {

    Code::Code(std::string code) : code(std::move(code)) {}

    char Code::charAt(size_t index) const {
        return code[index];
    }

    std::string_view Code::substr(size_t from, size_t to) const {
        assert(to > from);
        return std::string_view(code.data() + from, to - from);
    }

    std::string_view Code::str() const {
        return std::string_view(code);
    }

    CodeReference Code::ref(size_t from, size_t to) const {
        return CodeReference(from, to, code);
    }

    size_t Code::size() const {
        return code.size();
    }

    CodeReference::CodeReference(size_t from, size_t to, std::string_view code) :
        from(from), to(to), code(code) {}

    size_t CodeReference::getFrom() const {
        return from;
    }

    size_t CodeReference::getTo() const {
        return to;
    }

    std::string_view CodeReference::str() const {
        return code.substr(from, to - from);
    }

    CodeReference CodeReference::combine(const CodeReference &a, const CodeReference &b) {
        return CodeReference(a.getFrom(), b.getTo(), a.code);
    }

} // namespace evaluate
