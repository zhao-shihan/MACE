#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/InputNumericVector.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/ToSigned.hxx"

#include "gsl/gsl"

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace MACE::Utility {

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, {x, y, z});
///      AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N, Concept::NumericVector<T, N> V>
decltype(auto) AssignVector(V& lhs, V&& rhs) {
    return lhs = std::forward<decltype(rhs)>(rhs);
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, {x, y, z});
///      AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N, Concept::NumericVector<T, N> V>
decltype(auto) AssignVector(V& lhs, auto&& rhs)
    requires(not std::same_as<decltype(rhs), V &&> and
             std::assignable_from<V&, decltype(rhs)>)
{
    return lhs = std::forward<decltype(rhs)>(rhs);
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, {x, y, z});
///      AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N, Concept::NumericVector<T, N> V>
decltype(auto) AssignVector(V& lhs, std::ranges::input_range auto&& rhs)
    requires(not std::same_as<decltype(rhs), V &&> and
             not std::assignable_from<V&, decltype(rhs)> and
             requires(gsl::index i) { lhs[i] = std::forward<decltype(*std::ranges::begin(rhs))>(*std::ranges::begin(rhs)); })
{
    for (gsl::index i = 0; auto&& value : rhs) {
        lhs[i] = std::forward<decltype(value)>(value);
        ++i;
    }
    return lhs;
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, {x, y, z});
///      AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N, Concept::NumericVector<T, N> V>
decltype(auto) AssignVector(V& lhs, auto&& rhs)
    requires(not std::same_as<decltype(rhs), V &&> and
             not std::assignable_from<V&, decltype(rhs)> and
             not std::ranges::range<decltype(rhs)> and
             Concept::InputNumericVectorAny<std::remove_cvref_t<decltype(rhs)>, N> and
             requires(gsl::index i) { lhs[i] = std::forward<decltype(rhs[i])>(rhs[i]); })
{
    for (gsl::index i = 0; i < ToSigned(N); ++i) {
        lhs[i] = std::forward<decltype(rhs[i])>(rhs[i]);
    }
    return lhs;
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. AssignVector<double, 3>(u, v); AssignVector<double, 3>(u, {x, y, z});
///      AssignVector<double, 3>(u, x, y, z);
/// @tparam T The value type of the LHS vector.
/// @tparam N The dimension of the LHS vector
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
template<Concept::Arithmetic T, std::size_t N>
decltype(auto) AssignVector(Concept::NumericVector<T, N> auto& lhs, auto... rhs)
    requires(std::same_as<std::common_type_t<T, decltype(rhs)...>, T> and
             sizeof...(rhs) == N)
{
    return lhs = {std::forward<decltype(rhs)>(rhs)...};
}

/// @brief An alias of AssignVector<T, 2>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<T, 2> returns.
template<Concept::Arithmetic T>
decltype(auto) AssignVector2(Concept::NumericVector<T, 2> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 2)
{
    return AssignVector<T, 2>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<T, 3>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<T, 3> returns.
template<Concept::Arithmetic T>
decltype(auto) AssignVector3(Concept::NumericVector<T, 3> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 3)
{
    return AssignVector<T, 3>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector<T, 4>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector<T, 4> returns.
template<Concept::Arithmetic T>
decltype(auto) AssignVector4(Concept::NumericVector<T, 4> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 4)
{
    return AssignVector<T, 4>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector2<float>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector2<float> returns.
decltype(auto) AssignVector2F(Concept::NumericVector<float, 2> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 2)
{
    return AssignVector2<float>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector3<float>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector3<float> returns.
decltype(auto) AssignVector3F(Concept::NumericVector<float, 3> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 3)
{
    return AssignVector3<float>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector4<float>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector4<float> returns.
decltype(auto) AssignVector4F(Concept::NumericVector<float, 4> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 4)
{
    return AssignVector4<float>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector2<double>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector2<double> returns.
decltype(auto) AssignVector2D(Concept::NumericVector<double, 2> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 2)
{
    return AssignVector2<double>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector3<double>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector3<double> returns.
decltype(auto) AssignVector3D(Concept::NumericVector<double, 3> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 3)
{
    return AssignVector3<double>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

/// @brief An alias of AssignVector4<double>.
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return What AssignVector4<double> returns.
decltype(auto) AssignVector4D(Concept::NumericVector<double, 4> auto& lhs, auto&&... rhs)
    requires(sizeof...(rhs) == 1 or
             sizeof...(rhs) == 4)
{
    return AssignVector4<double>(lhs, std::forward<decltype(rhs)>(rhs)...);
}

} // namespace MACE::Utility
