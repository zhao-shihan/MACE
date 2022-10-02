#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Concept/Subscriptable.hxx"

#include "gsl/gsl"

#include <concepts>
#include <cstddef>
#include <utility>

namespace MACE::Utility {

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N>
decltype(auto) AssignVector(Concept::NumericVector<T, N> auto& lhs, auto&& rhs) requires
    std::assignable_from<decltype(lhs), decltype(rhs)> {
    return lhs = rhs;
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N>
decltype(auto) AssignVector(Concept::NumericVector<T, N> auto& lhs, Concept::Subscriptable auto&& rhs) requires(
    not std::assignable_from<decltype(lhs), decltype(rhs)>) {
    for (gsl::index i = 0; i < N; ++i) {
        lhs[i] = rhs[i];
    }
    return lhs;
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N>
decltype(auto) AssignVector(Concept::NumericVector<T, N> auto& lhs, std::same_as<T> auto... rhs) requires(
    sizeof...(rhs) == N) {
    return AssignVector<T, N>(lhs, std::array{rhs...});
}

/// @brief An alias of AssignVector<double, 2>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<double, 2> returns.
decltype(auto) AssignVector2D(Concept::NumericVector<double, 2> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 2) {
    return AssignVector<double, 2>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<double, 3>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<double, 3> returns.
decltype(auto) AssignVector3D(Concept::NumericVector<double, 3> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 3) {
    return AssignVector<double, 3>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<double, 4>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<double, 4> returns.
decltype(auto) AssignVector4D(Concept::NumericVector<double, 4> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 4) {
    return AssignVector<double, 4>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<float, 2>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<float, 2> returns.
decltype(auto) AssignVector2F(Concept::NumericVector<float, 2> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 2) {
    return AssignVector<float, 2>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<float, 3>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<float, 3> returns.
decltype(auto) AssignVector3F(Concept::NumericVector<float, 3> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 3) {
    return AssignVector<float, 3>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<float, 4>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<float, 4> returns.
decltype(auto) AssignVector4F(Concept::NumericVector<float, 4> auto& lhs, auto&&... rhs) requires(
    sizeof...(rhs) == 1 or sizeof...(rhs) == 4) {
    return AssignVector<float, 4>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

} // namespace MACE::Utility
