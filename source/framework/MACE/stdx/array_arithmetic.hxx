#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/stdx/array_alias.hxx"

#include <type_traits>

namespace MACE::stdx::array_arithmetic {

///////////////////////////////////////////////////////////////
// stdx::array2
///////////////////////////////////////////////////////////////

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array2<std::common_type_t<T, U>> operator+(const stdx::array2<T>& u, const stdx::array2<U>& v) {
    return {u[0] + v[0],
            u[1] + v[1]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array2<std::common_type_t<T, U>> operator-(const stdx::array2<T>& u, const stdx::array2<U>& v) {
    return {u[0] - v[0],
            u[1] - v[1]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array2<std::common_type_t<T, U>> operator*(const stdx::array2<T>& u, U c) {
    return {u[0] * c,
            u[1] * c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array2<std::common_type_t<T, U>> operator*(T c, const stdx::array2<U>& u) {
    return {c * u[0],
            c * u[1]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array2<std::common_type_t<T, U>> operator/(const stdx::array2<T>& u, U c) {
    return {u[0] / c,
            u[1] / c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto operator*(const stdx::array2<T>& u, const stdx::array2<U>& v) {
    return u[0] * v[0] + u[1] * v[1];
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator+=(stdx::array2<T>& u, const stdx::array2<U>& v) {
    u[0] += v[0];
    u[1] += v[1];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator-=(stdx::array2<T>& u, const stdx::array2<U>& v) {
    u[0] -= v[0];
    u[1] -= v[1];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator*=(stdx::array2<T>& u, U c) {
    u[0] *= c;
    u[1] *= c;
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator/=(stdx::array2<T>& u, U c) {
    u[0] /= c;
    u[1] /= c;
    return u;
}

///////////////////////////////////////////////////////////////
// stdx::array3
///////////////////////////////////////////////////////////////

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array3<std::common_type_t<T, U>> operator+(const stdx::array3<T>& u, const stdx::array3<U>& v) {
    return {u[0] + v[0],
            u[1] + v[1],
            u[2] + v[2]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array3<std::common_type_t<T, U>> operator-(const stdx::array3<T>& u, const stdx::array3<U>& v) {
    return {u[0] - v[0],
            u[1] - v[1],
            u[2] - v[2]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array3<std::common_type_t<T, U>> operator*(const stdx::array3<T>& u, U c) {
    return {u[0] * c,
            u[1] * c,
            u[2] * c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array3<std::common_type_t<T, U>> operator*(T c, const stdx::array3<U>& u) {
    return {c * u[0],
            c * u[1],
            c * u[2]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array3<std::common_type_t<T, U>> operator/(const stdx::array3<T>& u, U c) {
    return {u[0] / c,
            u[1] / c,
            u[2] / c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto operator*(const stdx::array3<T>& u, const stdx::array3<U>& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator+=(stdx::array3<T>& u, const stdx::array3<U>& v) {
    u[0] += v[0];
    u[1] += v[1];
    u[2] += v[2];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator-=(stdx::array3<T>& u, const stdx::array3<U>& v) {
    u[0] -= v[0];
    u[1] -= v[1];
    u[2] -= v[2];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator*=(stdx::array3<T>& u, U c) {
    u[0] *= c;
    u[1] *= c;
    u[2] *= c;
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator/=(stdx::array3<T>& u, U c) {
    u[0] /= c;
    u[1] /= c;
    u[2] /= c;
    return u;
}

///////////////////////////////////////////////////////////////
// stdx::array4
///////////////////////////////////////////////////////////////

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array4<std::common_type_t<T, U>> operator+(const stdx::array4<T>& u, const stdx::array4<U>& v) {
    return {u[0] + v[0],
            u[1] + v[1],
            u[2] + v[2],
            u[3] + v[3]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array4<std::common_type_t<T, U>> operator-(const stdx::array4<T>& u, const stdx::array4<U>& v) {
    return {u[0] - v[0],
            u[1] - v[1],
            u[2] - v[2],
            u[3] - v[3]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array4<std::common_type_t<T, U>> operator*(const stdx::array4<T>& u, U c) {
    return {u[0] * c,
            u[1] * c,
            u[2] * c,
            u[3] * c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array4<std::common_type_t<T, U>> operator*(T c, const stdx::array4<U>& u) {
    return {c * u[0],
            c * u[1],
            c * u[2],
            c * u[3]};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
stdx::array4<std::common_type_t<T, U>> operator/(const stdx::array4<T>& u, U c) {
    return {u[0] / c,
            u[1] / c,
            u[2] / c,
            u[3] / c};
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator+=(stdx::array4<T>& u, const stdx::array4<U>& v) {
    u[0] += v[0];
    u[1] += v[1];
    u[2] += v[2];
    u[3] += v[3];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator-=(stdx::array4<T>& u, const stdx::array4<U>& v) {
    u[0] -= v[0];
    u[1] -= v[1];
    u[2] -= v[2];
    u[3] -= v[3];
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator*=(stdx::array4<T>& u, U c) {
    u[0] *= c;
    u[1] *= c;
    u[2] *= c;
    u[3] *= c;
    return u;
}

template<Concept::Arithmetic T, Concept::Arithmetic U>
auto& operator/=(stdx::array4<T>& u, U c) {
    u[0] /= c;
    u[1] /= c;
    u[2] /= c;
    u[3] /= c;
    return u;
}

} // namespace MACE::stdx::array_arithmetic
