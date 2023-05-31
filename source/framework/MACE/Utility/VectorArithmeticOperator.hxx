#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/NumericVector.hxx"

#include <type_traits>

namespace MACE::inline Utility::inline VectorArithmeticOperator {

inline namespace Vector2ArithmeticOperator {

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(T, U) \
                                                                               \
    auto operator+(const Concept::NumericVector2<T> auto& u,                   \
                   const Concept::NumericVector2<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] + v[0],                                                   \
                u[1] + v[1]};                                                  \
    }                                                                          \
                                                                               \
    auto operator-(const Concept::NumericVector2<T> auto& u,                   \
                   const Concept::NumericVector2<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] - v[0],                                                   \
                u[1] - v[1]};                                                  \
    }                                                                          \
                                                                               \
    auto operator*(const Concept::NumericVector2<T> auto& u,                   \
                   const Concept::NumericVector2<U> auto& v) {                 \
        return u[0] * v[0] +                                                   \
               u[1] * v[1];                                                    \
    }                                                                          \
                                                                               \
    auto& operator+=(Concept::NumericVector2<T> auto& u,                       \
                     const Concept::NumericVector2<U> auto& v) {               \
        u[0] += v[0];                                                          \
        u[1] += v[1];                                                          \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto& operator-=(Concept::NumericVector2<T> auto& u,                       \
                     const Concept::NumericVector2<U> auto& v) {               \
        u[0] -= v[0];                                                          \
        u[1] -= v[1];                                                          \
        return u;                                                              \
    }

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(T) \
                                                                            \
    auto operator*(const Concept::NumericVector2<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] * c,                                                   \
                u[1] * c};                                                  \
    }                                                                       \
                                                                            \
    auto operator*(Concept::Arithmetic auto c,                              \
                   const Concept::NumericVector2<T> auto& u)                \
        ->std::decay_t<decltype(u)> {                                       \
        return {c * u[0],                                                   \
                c * u[1]};                                                  \
    }                                                                       \
                                                                            \
    auto operator/(const Concept::NumericVector2<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] / c,                                                   \
                u[1] / c};                                                  \
    }                                                                       \
                                                                            \
    auto& operator*=(Concept::NumericVector2<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] *= c;                                                          \
        u[1] *= c;                                                          \
        return u;                                                           \
    }                                                                       \
                                                                            \
    auto& operator/=(Concept::NumericVector2<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] /= c;                                                          \
        u[1] /= c;                                                          \
        return u;                                                           \
    }

MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(long double)

#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS
#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS

} // namespace Vector2ArithmeticOperator

inline namespace Vector3ArithmeticOperator {

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(T, U) \
                                                                               \
    auto operator+(const Concept::NumericVector3<T> auto& u,                   \
                   const Concept::NumericVector3<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] + v[0],                                                   \
                u[1] + v[1],                                                   \
                u[2] + v[2]};                                                  \
    }                                                                          \
                                                                               \
    auto operator-(const Concept::NumericVector3<T> auto& u,                   \
                   const Concept::NumericVector3<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] - v[0],                                                   \
                u[1] - v[1],                                                   \
                u[2] - v[2]};                                                  \
    }                                                                          \
                                                                               \
    auto operator*(const Concept::NumericVector3<T> auto& u,                   \
                   const Concept::NumericVector3<U> auto& v) {                 \
        return u[0] * v[0] +                                                   \
               u[1] * v[1] +                                                   \
               u[2] * v[2];                                                    \
    }                                                                          \
                                                                               \
    auto& operator+=(Concept::NumericVector3<T> auto& u,                       \
                     const Concept::NumericVector3<U> auto& v) {               \
        u[0] += v[0];                                                          \
        u[1] += v[1];                                                          \
        u[2] += v[2];                                                          \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto& operator-=(Concept::NumericVector3<T> auto& u,                       \
                     const Concept::NumericVector3<U> auto& v) {               \
        u[0] -= v[0];                                                          \
        u[1] -= v[1];                                                          \
        u[2] -= v[2];                                                          \
        return u;                                                              \
    }

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(T) \
                                                                            \
    auto operator*(const Concept::NumericVector3<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] * c,                                                   \
                u[1] * c,                                                   \
                u[2] * c};                                                  \
    }                                                                       \
                                                                            \
    auto operator*(Concept::Arithmetic auto c,                              \
                   const Concept::NumericVector3<T> auto& u)                \
        ->std::decay_t<decltype(u)> {                                       \
        return {c * u[0],                                                   \
                c * u[1],                                                   \
                c * u[2]};                                                  \
    }                                                                       \
                                                                            \
    auto operator/(const Concept::NumericVector3<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] / c,                                                   \
                u[1] / c,                                                   \
                u[2] / c};                                                  \
    }                                                                       \
                                                                            \
    auto& operator*=(Concept::NumericVector3<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] *= c;                                                          \
        u[1] *= c;                                                          \
        u[2] *= c;                                                          \
        return u;                                                           \
    }                                                                       \
                                                                            \
    auto& operator/=(Concept::NumericVector3<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] /= c;                                                          \
        u[1] /= c;                                                          \
        u[2] /= c;                                                          \
        return u;                                                           \
    }

MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(long double)

#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS
#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS

} // namespace Vector3ArithmeticOperator

inline namespace Vector4ArithmeticOperator {

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(T, U) \
                                                                               \
    auto operator+(const Concept::NumericVector4<T> auto& u,                   \
                   const Concept::NumericVector4<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] + v[0],                                                   \
                u[1] + v[1],                                                   \
                u[2] + v[2],                                                   \
                u[3] + v[3]};                                                  \
    }                                                                          \
                                                                               \
    auto operator-(const Concept::NumericVector4<T> auto& u,                   \
                   const Concept::NumericVector4<U> auto& v)                   \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                           \
                             std::decay_t<decltype(u)>,                        \
                             std::decay_t<decltype(v)>> {                      \
        return {u[0] - v[0],                                                   \
                u[1] - v[1],                                                   \
                u[2] - v[2],                                                   \
                u[3] - v[3]};                                                  \
    }                                                                          \
                                                                               \
    auto& operator+=(Concept::NumericVector4<T> auto& u,                       \
                     const Concept::NumericVector4<U> auto& v) {               \
        u[0] += v[0];                                                          \
        u[1] += v[1];                                                          \
        u[2] += v[2];                                                          \
        u[3] += v[3];                                                          \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto& operator-=(Concept::NumericVector4<T> auto& u,                       \
                     const Concept::NumericVector4<U> auto& v) {               \
        u[0] -= v[0];                                                          \
        u[1] -= v[1];                                                          \
        u[2] -= v[2];                                                          \
        u[3] -= v[3];                                                          \
        return u;                                                              \
    }

#define MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(T) \
                                                                            \
    auto operator*(const Concept::NumericVector4<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] * c,                                                   \
                u[1] * c,                                                   \
                u[2] * c,                                                   \
                u[3] * c};                                                  \
    }                                                                       \
                                                                            \
    auto operator*(Concept::Arithmetic auto c,                              \
                   const Concept::NumericVector4<T> auto& u)                \
        ->std::decay_t<decltype(u)> {                                       \
        return {c * u[0],                                                   \
                c * u[1],                                                   \
                c * u[2],                                                   \
                c * u[3]};                                                  \
    }                                                                       \
                                                                            \
    auto operator/(const Concept::NumericVector4<T> auto& u,                \
                   Concept::Arithmetic auto c)                              \
        ->std::decay_t<decltype(u)> {                                       \
        return {u[0] / c,                                                   \
                u[1] / c,                                                   \
                u[2] / c,                                                   \
                u[3] / c};                                                  \
    }                                                                       \
                                                                            \
    auto& operator*=(Concept::NumericVector4<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] *= c;                                                          \
        u[1] *= c;                                                          \
        u[2] *= c;                                                          \
        u[3] *= c;                                                          \
        return u;                                                           \
    }                                                                       \
                                                                            \
    auto& operator/=(Concept::NumericVector4<T> auto& u,                    \
                     Concept::Arithmetic auto c) {                          \
        u[0] /= c;                                                          \
        u[1] /= c;                                                          \
        u[2] /= c;                                                          \
        u[3] /= c;                                                          \
        return u;                                                           \
    }

MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, long double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(float)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(double)
MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(long double)

#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS
#undef MACE_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS

} // namespace Vector4ArithmeticOperator

} // namespace MACE::inline Utility::inline VectorArithmeticOperator
