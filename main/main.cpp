#include <Evaluator.hpp>
#include <analyze/ASTPrinter.hpp>
#include <analyze/Analyzer.hpp>
#include <iostream>
#include <lex/Lexer.hpp>
#include <parse/NodePrinter.hpp>
#include <parse/Parser.hpp>
#include <util/Code.hpp>

using namespace evaluate;
using namespace std;

int main() {
    cout << eval("1+2-3*4/5") << endl;
    cout << eval("-2 ** 4") << endl;
    cout << eval("-2 ** 3") << endl;
    cout << eval("1 + pow(2 , 10)") << endl;
    return 0;
}