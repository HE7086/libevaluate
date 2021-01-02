#include "Error.hpp"
#include "Code.hpp"
#include <iostream>
#include <iomanip>

namespace evaluate {

    void error(size_t offset, size_t size, const Code &code, const std::string& msg) {
        std::cerr << "Error at offset: " << offset << " with length: " << size << std::endl;
        std::cerr << code.str() << std::endl;
        std::cerr << std::setfill(' ') << std::setw(static_cast<int>(offset)) << "";
        std::cerr << std::setfill('^') << std::setw(static_cast<int>(size)) << "" << std::endl;
        std::cerr << "***" << msg << std::endl;
        exit(1);
    }

    void error(const std::string& msg) {
        std::cerr << msg << std::endl;
        exit(1);
    }

} // namespace evaluate
