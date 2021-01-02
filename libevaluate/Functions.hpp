#pragma once

#include "util/Error.hpp"
#include <cmath>
#include <concepts>
#include <functional>
#include <string>
#include <unordered_map>
#include <variant>
#include <type_traits>

namespace evaluate {

static inline double getAsDouble(std::variant<int64_t, double> value) {
    if (holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else {
        return static_cast<double>(std::get<int64_t>(value));
    }
}

enum class FunctionType {
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
};
template <FunctionType> static constexpr inline int functionParams();
template <> constexpr inline int functionParams<FunctionType::abs>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::div>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::fmod>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::remainder>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::fma>() { return 3; }
template <> constexpr inline int functionParams<FunctionType::fmax>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::fmin>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::fdim>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::exp>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::exp2>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::expm1>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::log>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::log10>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::log2>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::log1p>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::pow>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::sqrt>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::cbrt>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::hypot>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::sin>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::cos>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::tan>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::asin>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::acos>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::atan>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::atan2>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::sinh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::cosh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::tanh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::asinh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::acosh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::atanh>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::erf>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::erfc>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::tgamma>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::lgamma>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::ceil>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::floor>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::trunc>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::round>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::nearbyint>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::rint>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::ldexp>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::scalbn>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::ilogb>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::logb>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::nextafter>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::copysign>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::assoc_laguerre>() { return 3; }
template <> constexpr inline int functionParams<FunctionType::assoc_legendre>() { return 3; }
template <> constexpr inline int functionParams<FunctionType::beta>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::comp_ellint_1>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::comp_ellint_2>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::comp_ellint_3>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::cyl_bessel_i>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::cyl_bessel_j>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::cyl_bessel_k>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::cyl_neumann>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::ellint_1>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::ellint_2>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::ellint_3>() { return 3; }
template <> constexpr inline int functionParams<FunctionType::expint>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::hermite>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::legendre>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::laguerre>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::riemann_zeta>() { return 1; }
template <> constexpr inline int functionParams<FunctionType::sph_bessel>() { return 2; }
template <> constexpr inline int functionParams<FunctionType::sph_legendre>() { return 3; }
template <> constexpr inline int functionParams<FunctionType::sph_neumann>() { return 2; }

template <FunctionType type>
requires(functionParams<type>() == 1) static inline std::variant<int64_t, double> functionCall(
    std::variant<int64_t, double>& param);

template <FunctionType type>
requires(functionParams<type>() == 2) static inline std::variant<int64_t, double> functionCall(
    std::variant<int64_t, double>& param1, std::variant<int64_t, double>& param2);

template <FunctionType type>
requires(functionParams<type>() == 3) static inline std::variant<int64_t, double> functionCall(
    std::variant<int64_t, double>& param1,
    std::variant<int64_t, double>& param2,
    std::variant<int64_t, double>& param3);

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::abs>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::fabs(std::get<double>(param));
    } else {
        return std::abs(std::get<int64_t>(param));
    }
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::div>(std::variant<int64_t, double>& param1,
                                std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        error("Evaluation Error: invalid usage of div on floating points");
    }
    return std::div(std::get<int64_t>(param1), std::get<int64_t>(param2)).quot;
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::fmod>(std::variant<int64_t, double>& param1,
                                 std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<int64_t>(param1) || std::holds_alternative<int64_t>(param2)) {
        error("Evaluation Error: invalid usage of div on integers");
    }
    return std::fmod(std::get<double>(param1), std::get<double>(param2));
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::remainder>(std::variant<int64_t, double>& param1,
                                      std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::remainder(getAsDouble(param1), getAsDouble(param2));
    }
    return std::remainder(std::get<int64_t>(param1), std::get<int64_t>(param2));
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::fma>(std::variant<int64_t, double>& param1,
                                std::variant<int64_t, double>& param2,
                                std::variant<int64_t, double>& param3) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2) ||
        std::holds_alternative<double>(param3)) {
        return std::fma(getAsDouble(param1), getAsDouble(param2), getAsDouble(param3));
    }
    return std::fma(std::get<int64_t>(param1),
                    std::get<int64_t>(param2),
                    std::get<int64_t>(param3));
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::fmax>(std::variant<int64_t, double>& param1,
                                 std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::fmax(getAsDouble(param1), getAsDouble(param2));
    }
    return std::fmax(std::get<int64_t>(param1), std::get<int64_t>(param2));
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::fmin>(std::variant<int64_t, double>& param1,
                                 std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::fmin(getAsDouble(param1), getAsDouble(param2));
    }
    return std::fmin(std::get<int64_t>(param1), std::get<int64_t>(param2));
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::fdim>(std::variant<int64_t, double>& param1,
                                 std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::fdim(getAsDouble(param1), getAsDouble(param2));
    }
    return std::fdim(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::exp>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::exp(std::get<double>(param));
    } else {
        return std::exp(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::exp2>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::exp2(std::get<double>(param));
    } else {
        return std::exp2(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::expm1>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::expm1(std::get<double>(param));
    } else {
        return std::expm1(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::log>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::log(std::get<double>(param));
    } else {
        return std::log(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::log10>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::log10(std::get<double>(param));
    } else {
        return std::log10(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::log2>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::log2(std::get<double>(param));
    } else {
        return std::log2(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::log1p>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::log1p(std::get<double>(param));
    } else {
        return std::log1p(std::get<int64_t>(param));
    }
}

template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::pow>(std::variant<int64_t, double>& param1,
                                std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::pow(getAsDouble(param1), getAsDouble(param2));
    }
    return std::pow(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sqrt>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::sqrt(std::get<double>(param));
    } else {
        return std::sqrt(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cbrt>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::cbrt(std::get<double>(param));
    } else {
        return std::cbrt(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::hypot>(std::variant<int64_t, double>& param1,
                                  std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::hypot(getAsDouble(param1), getAsDouble(param2));
    }
    return std::hypot(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sin>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::sin(std::get<double>(param));
    } else {
        return std::sin(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cos>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::cos(std::get<double>(param));
    } else {
        return std::cos(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::tan>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::tan(std::get<double>(param));
    } else {
        return std::tan(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::asin>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::asin(std::get<double>(param));
    } else {
        return std::asin(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::acos>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::acos(std::get<double>(param));
    } else {
        return std::acos(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::atan>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::atan(std::get<double>(param));
    } else {
        return std::atan(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::atan2>(std::variant<int64_t, double>& param1,
                                  std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::atan2(getAsDouble(param1), getAsDouble(param2));
    }
    return std::atan2(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sinh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::sinh(std::get<double>(param));
    } else {
        return std::sinh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cosh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::cosh(std::get<double>(param));
    } else {
        return std::cosh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::tanh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::tanh(std::get<double>(param));
    } else {
        return std::tanh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::asinh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::asinh(std::get<double>(param));
    } else {
        return std::asinh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::acosh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::acosh(std::get<double>(param));
    } else {
        return std::acosh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::atanh>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::atanh(std::get<double>(param));
    } else {
        return std::atanh(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::erf>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::erf(std::get<double>(param));
    } else {
        return std::erf(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::erfc>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::erfc(std::get<double>(param));
    } else {
        return std::erfc(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::tgamma>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::tgamma(std::get<double>(param));
    } else {
        return std::tgamma(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::lgamma>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::lgamma(std::get<double>(param));
    } else {
        return std::lgamma(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ceil>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::ceil(std::get<double>(param));
    } else {
        return std::ceil(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::floor>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::floor(std::get<double>(param));
    } else {
        return std::floor(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::trunc>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::trunc(std::get<double>(param));
    } else {
        return std::trunc(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::round>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::round(std::get<double>(param));
    } else {
        return std::round(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::nearbyint>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::nearbyint(std::get<double>(param));
    } else {
        return std::nearbyint(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::rint>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::rint(std::get<double>(param));
    } else {
        return std::rint(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ldexp>(std::variant<int64_t, double>& param1,
                                  std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::ldexp(getAsDouble(param1), static_cast<int>(getAsDouble(param2)));
    }
    return std::ldexp(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::scalbn>(std::variant<int64_t, double>& param1,
                                   std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::scalbn(getAsDouble(param1), static_cast<int>(getAsDouble(param2)));
    }
    return std::scalbn(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ilogb>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::ilogb(std::get<double>(param));
    } else {
        return std::ilogb(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::logb>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::logb(std::get<double>(param));
    } else {
        return std::logb(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::nextafter>(std::variant<int64_t, double>& param1,
                                      std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::nextafter(getAsDouble(param1), getAsDouble(param2));
    }
    return std::nextafter(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::copysign>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::copysign(getAsDouble(param1), getAsDouble(param2));
    }
    return std::copysign(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::assoc_laguerre>(std::variant<int64_t, double>& param1,
                                           std::variant<int64_t, double>& param2,
                                           std::variant<int64_t, double>& param3) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2) ||
        std::holds_alternative<double>(param3)) {
        return std::assoc_laguerre(static_cast<int64_t>(getAsDouble(param1)),
                                   static_cast<int64_t>(getAsDouble(param2)),
                                   getAsDouble(param3));
    }
    return std::assoc_laguerre(std::get<int64_t>(param1),
                               std::get<int64_t>(param2),
                               std::get<int64_t>(param3));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::assoc_legendre>(std::variant<int64_t, double>& param1,
                                           std::variant<int64_t, double>& param2,
                                           std::variant<int64_t, double>& param3) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2) ||
        std::holds_alternative<double>(param3)) {
        return std::assoc_legendre(static_cast<int64_t>(getAsDouble(param1)),
                                   static_cast<int64_t>(getAsDouble(param2)),
                                   getAsDouble(param3));
    }
    return std::assoc_legendre(std::get<int64_t>(param1),
                               std::get<int64_t>(param2),
                               std::get<int64_t>(param3));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::beta>(std::variant<int64_t, double>& param1,
                                 std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::beta(getAsDouble(param1), getAsDouble(param2));
    }
    return std::beta(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::comp_ellint_1>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::comp_ellint_1(std::get<double>(param));
    } else {
        return std::comp_ellint_1(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::comp_ellint_2>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::comp_ellint_2(std::get<double>(param));
    } else {
        return std::comp_ellint_2(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::comp_ellint_3>(std::variant<int64_t, double>& param1,
                                          std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::comp_ellint_3(getAsDouble(param1), getAsDouble(param2));
    }
    return std::comp_ellint_3(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cyl_bessel_i>(std::variant<int64_t, double>& param1,
                                         std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::cyl_bessel_i(getAsDouble(param1), getAsDouble(param2));
    }
    return std::cyl_bessel_i(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cyl_bessel_j>(std::variant<int64_t, double>& param1,
                                         std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::cyl_bessel_j(getAsDouble(param1), getAsDouble(param2));
    }
    return std::cyl_bessel_j(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cyl_bessel_k>(std::variant<int64_t, double>& param1,
                                         std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::cyl_bessel_k(getAsDouble(param1), getAsDouble(param2));
    }
    return std::cyl_bessel_k(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::cyl_neumann>(std::variant<int64_t, double>& param1,
                                        std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::cyl_neumann(getAsDouble(param1), getAsDouble(param2));
    }
    return std::cyl_neumann(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ellint_1>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::ellint_1(getAsDouble(param1), getAsDouble(param2));
    }
    return std::ellint_1(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ellint_2>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::ellint_2(getAsDouble(param1), getAsDouble(param2));
    }
    return std::ellint_2(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::ellint_3>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2,
                                     std::variant<int64_t, double>& param3) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2) ||
        std::holds_alternative<double>(param3)) {
        return std::ellint_3(getAsDouble(param1), getAsDouble(param2), getAsDouble(param3));
    }
    return std::ellint_3(std::get<int64_t>(param1),
                         std::get<int64_t>(param2),
                         std::get<int64_t>(param3));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::expint>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::expint(std::get<double>(param));
    } else {
        return std::expint(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::hermite>(std::variant<int64_t, double>& param1,
                                    std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::hermite(static_cast<int64_t>(getAsDouble(param1)), getAsDouble(param2));
    }
    return std::hermite(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::legendre>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::legendre(static_cast<int64_t>(getAsDouble(param1)), getAsDouble(param2));
    }
    return std::legendre(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::laguerre>(std::variant<int64_t, double>& param1,
                                     std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::laguerre(static_cast<int64_t>(getAsDouble(param1)), getAsDouble(param2));
    }
    return std::laguerre(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::riemann_zeta>(std::variant<int64_t, double>& param) {
    if (std::holds_alternative<double>(param)) {
        return std::riemann_zeta(std::get<double>(param));
    } else {
        return std::riemann_zeta(std::get<int64_t>(param));
    }
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sph_bessel>(std::variant<int64_t, double>& param1,
                                       std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::sph_bessel(static_cast<int64_t>(getAsDouble(param1)), getAsDouble(param2));
    }
    return std::sph_bessel(std::get<int64_t>(param1), std::get<int64_t>(param2));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sph_legendre>(std::variant<int64_t, double>& param1,
                                         std::variant<int64_t, double>& param2,
                                         std::variant<int64_t, double>& param3) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2) ||
        std::holds_alternative<double>(param3)) {
        return std::sph_legendre(static_cast<int64_t>(getAsDouble(param1)),
                                 static_cast<int64_t>(getAsDouble(param2)), getAsDouble(param3));
    }
    return std::sph_legendre(std::get<int64_t>(param1),
                             std::get<int64_t>(param2),
                             std::get<int64_t>(param3));
}
template <>
inline std::variant<int64_t, double>
functionCall<FunctionType::sph_neumann>(std::variant<int64_t, double>& param1,
                                        std::variant<int64_t, double>& param2) {
    if (std::holds_alternative<double>(param1) || std::holds_alternative<double>(param2)) {
        return std::sph_neumann(static_cast<int64_t>(getAsDouble(param1)), getAsDouble(param2));
    }
    return std::sph_neumann(std::get<int64_t>(param1), std::get<int64_t>(param2));
}

inline std::variant<int64_t, double> call(FunctionType type,
                                          std::vector<std::variant<int64_t, double>>& params) {
    // ugly hack :(
    switch (type) {
        case FunctionType::abs: {
            return functionCall<FunctionType::abs>(params[0]);
        }
        case FunctionType::div: {
            return functionCall<FunctionType::div>(params[0], params[1]);
        }
        case FunctionType::fmod: {
            return functionCall<FunctionType::fmod>(params[0], params[1]);
        }
        case FunctionType::remainder: {
            return functionCall<FunctionType::remainder>(params[0], params[1]);
        }
        case FunctionType::fma: {
            return functionCall<FunctionType::fma>(params[0], params[1], params[2]);
        }
        case FunctionType::fmax: {
            return functionCall<FunctionType::fmax>(params[0], params[1]);
        }
        case FunctionType::fmin: {
            return functionCall<FunctionType::fmin>(params[0], params[1]);
        }
        case FunctionType::fdim: {
            return functionCall<FunctionType::fdim>(params[0], params[1]);
        }
        case FunctionType::exp: {
            return functionCall<FunctionType::exp>(params[0]);
        }
        case FunctionType::exp2: {
            return functionCall<FunctionType::exp2>(params[0]);
        }
        case FunctionType::expm1: {
            return functionCall<FunctionType::expm1>(params[0]);
        }
        case FunctionType::log: {
            return functionCall<FunctionType::log>(params[0]);
        }
        case FunctionType::log10: {
            return functionCall<FunctionType::log10>(params[0]);
        }
        case FunctionType::log2: {
            return functionCall<FunctionType::log2>(params[0]);
        }
        case FunctionType::log1p: {
            return functionCall<FunctionType::log1p>(params[0]);
        }
        case FunctionType::pow: {
            return functionCall<FunctionType::pow>(params[0], params[1]);
        }
        case FunctionType::sqrt: {
            return functionCall<FunctionType::sqrt>(params[0]);
        }
        case FunctionType::cbrt: {
            return functionCall<FunctionType::cbrt>(params[0]);
        }
        case FunctionType::hypot: {
            return functionCall<FunctionType::hypot>(params[0], params[1]);
        }
        case FunctionType::sin: {
            return functionCall<FunctionType::sin>(params[0]);
        }
        case FunctionType::cos: {
            return functionCall<FunctionType::cos>(params[0]);
        }
        case FunctionType::tan: {
            return functionCall<FunctionType::tan>(params[0]);
        }
        case FunctionType::asin: {
            return functionCall<FunctionType::asin>(params[0]);
        }
        case FunctionType::acos: {
            return functionCall<FunctionType::acos>(params[0]);
        }
        case FunctionType::atan: {
            return functionCall<FunctionType::atan>(params[0]);
        }
        case FunctionType::atan2: {
            return functionCall<FunctionType::atan2>(params[0], params[1]);
        }
        case FunctionType::sinh: {
            return functionCall<FunctionType::sinh>(params[0]);
        }
        case FunctionType::cosh: {
            return functionCall<FunctionType::cosh>(params[0]);
        }
        case FunctionType::tanh: {
            return functionCall<FunctionType::tanh>(params[0]);
        }
        case FunctionType::asinh: {
            return functionCall<FunctionType::asinh>(params[0]);
        }
        case FunctionType::acosh: {
            return functionCall<FunctionType::acosh>(params[0]);
        }
        case FunctionType::atanh: {
            return functionCall<FunctionType::atanh>(params[0]);
        }
        case FunctionType::erf: {
            return functionCall<FunctionType::erf>(params[0]);
        }
        case FunctionType::erfc: {
            return functionCall<FunctionType::erfc>(params[0]);
        }
        case FunctionType::tgamma: {
            return functionCall<FunctionType::tgamma>(params[0]);
        }
        case FunctionType::lgamma: {
            return functionCall<FunctionType::lgamma>(params[0]);
        }
        case FunctionType::ceil: {
            return functionCall<FunctionType::ceil>(params[0]);
        }
        case FunctionType::floor: {
            return functionCall<FunctionType::floor>(params[0]);
        }
        case FunctionType::trunc: {
            return functionCall<FunctionType::trunc>(params[0]);
        }
        case FunctionType::round: {
            return functionCall<FunctionType::round>(params[0]);
        }
        case FunctionType::nearbyint: {
            return functionCall<FunctionType::nearbyint>(params[0]);
        }
        case FunctionType::rint: {
            return functionCall<FunctionType::rint>(params[0]);
        }
        case FunctionType::ldexp: {
            return functionCall<FunctionType::ldexp>(params[0], params[1]);
        }
        case FunctionType::scalbn: {
            return functionCall<FunctionType::scalbn>(params[0], params[1]);
        }
        case FunctionType::ilogb: {
            return functionCall<FunctionType::ilogb>(params[0]);
        }
        case FunctionType::logb: {
            return functionCall<FunctionType::logb>(params[0]);
        }
        case FunctionType::nextafter: {
            return functionCall<FunctionType::nextafter>(params[0], params[1]);
        }
        case FunctionType::copysign: {
            return functionCall<FunctionType::copysign>(params[0], params[1]);
        }
        case FunctionType::assoc_laguerre: {
            return functionCall<FunctionType::assoc_laguerre>(params[0], params[1], params[2]);
        }
        case FunctionType::assoc_legendre: {
            return functionCall<FunctionType::assoc_legendre>(params[0], params[1], params[2]);
        }
        case FunctionType::beta: {
            return functionCall<FunctionType::beta>(params[0], params[1]);
        }
        case FunctionType::comp_ellint_1: {
            return functionCall<FunctionType::comp_ellint_1>(params[0]);
        }
        case FunctionType::comp_ellint_2: {
            return functionCall<FunctionType::comp_ellint_2>(params[0]);
        }
        case FunctionType::comp_ellint_3: {
            return functionCall<FunctionType::comp_ellint_3>(params[0], params[1]);
        }
        case FunctionType::cyl_bessel_i: {
            return functionCall<FunctionType::cyl_bessel_i>(params[0], params[1]);
        }
        case FunctionType::cyl_bessel_j: {
            return functionCall<FunctionType::cyl_bessel_j>(params[0], params[1]);
        }
        case FunctionType::cyl_bessel_k: {
            return functionCall<FunctionType::cyl_bessel_k>(params[0], params[1]);
        }
        case FunctionType::cyl_neumann: {
            return functionCall<FunctionType::cyl_neumann>(params[0], params[1]);
        }
        case FunctionType::ellint_1: {
            return functionCall<FunctionType::ellint_1>(params[0], params[1]);
        }
        case FunctionType::ellint_2: {
            return functionCall<FunctionType::ellint_2>(params[0], params[1]);
        }
        case FunctionType::ellint_3: {
            return functionCall<FunctionType::ellint_3>(params[0], params[1], params[2]);
        }
        case FunctionType::expint: {
            return functionCall<FunctionType::expint>(params[0]);
        }
        case FunctionType::hermite: {
            return functionCall<FunctionType::hermite>(params[0], params[1]);
        }
        case FunctionType::legendre: {
            return functionCall<FunctionType::legendre>(params[0], params[1]);
        }
        case FunctionType::laguerre: {
            return functionCall<FunctionType::laguerre>(params[0], params[1]);
        }
        case FunctionType::riemann_zeta: {
            return functionCall<FunctionType::riemann_zeta>(params[0]);
        }
        case FunctionType::sph_bessel: {
            return functionCall<FunctionType::sph_bessel>(params[0], params[1]);
        }
        case FunctionType::sph_legendre: {
            return functionCall<FunctionType::sph_legendre>(params[0], params[1], params[2]);
        }
        case FunctionType::sph_neumann: {
            return functionCall<FunctionType::sph_neumann>(params[0], params[1]);
        }
        default: {
            error("unknown error");
        }
    }
}
static const std::unordered_map<std::string, FunctionType> functionNames{
    {"abs", FunctionType::abs},
    {"div", FunctionType::div},
    {"fmod", FunctionType::fmod},
    {"remainder", FunctionType::remainder},
    {"fma", FunctionType::fma},
    {"fmax", FunctionType::fmax},
    {"fmin", FunctionType::fmin},
    {"fdim", FunctionType::fdim},
    {"exp", FunctionType::exp},
    {"exp2", FunctionType::exp2},
    {"expm1", FunctionType::expm1},
    {"log", FunctionType::log},
    {"log10", FunctionType::log10},
    {"log2", FunctionType::log2},
    {"log1p", FunctionType::log1p},
    {"pow", FunctionType::pow},
    {"sqrt", FunctionType::sqrt},
    {"cbrt", FunctionType::cbrt},
    {"hypot", FunctionType::hypot},
    {"sin", FunctionType::sin},
    {"cos", FunctionType::cos},
    {"tan", FunctionType::tan},
    {"asin", FunctionType::asin},
    {"acos", FunctionType::acos},
    {"atan", FunctionType::atan},
    {"atan2", FunctionType::atan2},
    {"sinh", FunctionType::sinh},
    {"cosh", FunctionType::cosh},
    {"tanh", FunctionType::tanh},
    {"asinh", FunctionType::asinh},
    {"acosh", FunctionType::acosh},
    {"atanh", FunctionType::atanh},
    {"erf", FunctionType::erf},
    {"erfc", FunctionType::erfc},
    {"tgamma", FunctionType::tgamma},
    {"lgamma", FunctionType::lgamma},
    {"ceil", FunctionType::ceil},
    {"floor", FunctionType::floor},
    {"trunc", FunctionType::trunc},
    {"round", FunctionType::round},
    {"nearbyint", FunctionType::nearbyint},
    {"rint", FunctionType::rint},
    {"ldexp", FunctionType::ldexp},
    {"scalbn", FunctionType::scalbn},
    {"ilogb", FunctionType::ilogb},
    {"logb", FunctionType::logb},
    {"nextafter", FunctionType::nextafter},
    {"copysign", FunctionType::copysign},
    {"assoc_laguerre", FunctionType::assoc_laguerre},
    {"assoc_legendre", FunctionType::assoc_legendre},
    {"beta", FunctionType::beta},
    {"comp_ellint_1", FunctionType::comp_ellint_1},
    {"comp_ellint_2", FunctionType::comp_ellint_2},
    {"comp_ellint_3", FunctionType::comp_ellint_3},
    {"cyl_bessel_i", FunctionType::cyl_bessel_i},
    {"cyl_bessel_j", FunctionType::cyl_bessel_j},
    {"cyl_bessel_k", FunctionType::cyl_bessel_k},
    {"cyl_neumann", FunctionType::cyl_neumann},
    {"ellint_1", FunctionType::ellint_1},
    {"ellint_2", FunctionType::ellint_2},
    {"ellint_3", FunctionType::ellint_3},
    {"expint", FunctionType::expint},
    {"hermite", FunctionType::hermite},
    {"legendre", FunctionType::legendre},
    {"laguerre", FunctionType::laguerre},
    {"riemann_zeta", FunctionType::riemann_zeta},
    {"sph_bessel", FunctionType::sph_bessel},
    {"sph_legendre", FunctionType::sph_legendre},
    {"sph_neumann", FunctionType::sph_neumann}};
} // namespace evaluate