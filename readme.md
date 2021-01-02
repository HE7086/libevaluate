# libevaluate

a simple library to evaluate custom string expressions

> this project is made totally out of interest, and still under development.  
> so no guarantee for correctness

## Evaluation Strategy
The Evaluator basically mimic the behaviour of a compiler's front end. It will first lex the string, then parse it to AST nodes. These nodes will be used to evaluate the whole expression.

data flow:
```
string expression 
-> lexer (token stream) 
-> parser (parse tree) 
-> analyzer (AST) 
-> evaluator (value)
```

The evaluator works on either 64-bit signed integer or 64-bit floating point values, i.e. `std::variant<int64_t, double>` is used throughout the whole evaluation. It will try to work with integer values first, and only convert them to double when needed (by a function or any of the operand is double already)

There are several library functions (all of them are defined in \<cmath\>) supported by the evaluator. These functions are chosen such that no pointer or non-integral/double value are involved.

## Example
```c++
#include <iostream>
#include <Evaluator.hpp>
int main() {
    std::cout << eval("1 + 2 ** 3") << endl;
}
```

## Expression Specification

expression
 - pow_expression

function
 - \<function_name\>"(" expression, ... ")"

primary_expression 
 - literal 
 - ( pow_expression ) 
 - function( primary_expression )

unary_expression 
 - primary_expression
 - [+ | - | ~] unary_expression

pow_expression
 - or_expression
 - or_expression ** pow_expression

or_expression 
 - xor_expression 
 - xor_expression | or_expression

xor_expression 
 - and_expression
 - and_expression ^ xor_expression
 
and_expression
 - shift_expression
 - shift_expression & and_expression

shift_expression
 - additive_expression
 - additive_expression \<\< shift_expression
 - additive_expression \>\> shift_expression

additive_expression
 - multiplicative_expression
 - multiplicative_expression + additive_expression 
 - multiplicative_expression - additive_expression

multiplicative_expression
 - unary_expression
 - unary_expression * multiplicative_expression
 - unary_expression / multiplicative_expression
 - unary_expression % multiplicative_expression

### supported functions
abs,
div,
fmod,
remainder,
fma,
fmax,
fmin,
fdim,
exp,
exp2,
expm1,
log,
log10,
log2,
log1p,
pow,
sqrt,
cbrt,
hypot,
sin,
cos,
tan,
asin,
acos,
atan,
atan2,
sinh,
cosh,
tanh,
asinh,
acosh,
atanh,
erf,
erfc,
tgamma,
lgamma,
ceil,
floor,
trunc,
round,
nearbyint,
rint,
ldexp,
scalbn,
ilogb,
logb,
nextafter,
copysign,
assoc_laguerre,
assoc_legendre,
beta,
comp_ellint_1,
comp_ellint_2,
comp_ellint_3,
cyl_bessel_i,
cyl_bessel_j,
cyl_bessel_k,
cyl_neumann,
ellint_1,
ellint_2,
ellint_3,
expint,
hermite,
legendre,
laguerre,
riemann_zeta,
sph_bessel,
sph_legendre,
sph_neumann
