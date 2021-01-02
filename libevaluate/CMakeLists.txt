set(LIBEVALUATE_SOURCES
        lex/Lexer.cpp lex/Lexer.hpp
        parse/Parser.cpp parse/Parser.hpp
        lex/Token.cpp lex/Token.hpp
        util/Code.cpp util/Code.hpp
        util/Error.cpp util/Error.hpp
        parse/Node.cpp parse/Node.hpp
        parse/NodeVisitor.hpp
        parse/NodePrinter.cpp parse/NodePrinter.hpp
        analyze/AST.cpp analyze/AST.hpp
        analyze/Analyzer.cpp analyze/Analyzer.hpp
        analyze/ASTVisitor.hpp
        analyze/ASTPrinter.cpp analyze/ASTPrinter.hpp
        Evaluator.cpp Evaluator.hpp
        Functions.hpp)

add_library(libevaluate_core ${LIBEVALUATE_SOURCES})
target_include_directories(libevaluate_core PUBLIC ${CMAKE_SOURCE_DIR}/libevaluate)

add_clang_tidy_target(lint_libevaluate_core ${LIBEVALUATE_SOURCES})
add_dependencies(lint lint_libevaluate_core)