#pragma once

#include <cstddef>
#include <string>

namespace evaluate {

    class Code;

    [[noreturn]] void error(size_t offset, size_t size, const Code& code, const std::string& msg);
    [[noreturn]] void error(const std::string& msg);

} // namespace evaluate

