#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/Indirectable.hxx"
#include "MACE/Concept/InputVector.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/ToSigned.hxx"
#include "MACE/Utility/VectorDimension.hxx"
#include "MACE/Utility/VectorValueType.hxx"

#include "gsl/gsl"

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace MACE::inline Utility {

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. VectorAssign<double, 3>(u, v); VectorAssign<double, 3>(u, {x, y, z});
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
decltype(auto) VectorAssign(Concept::NumericVectorAny auto& lhs, auto&& rhs)
    requires(std::assignable_from<decltype(lhs), decltype(rhs)>)
{
    return lhs = std::forward<decltype(rhs)>(rhs);
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. VectorAssign<double, 3>(u, v); VectorAssign<double, 3>(u, {x, y, z});
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
decltype(auto) VectorAssign(Concept::NumericVectorAny auto& lhs, std::ranges::input_range auto&& rhs)
    requires(not std::assignable_from<decltype(lhs), decltype(rhs)> and
             std::assignable_from<VectorValueType<std::remove_cvref_t<decltype(lhs)>>&, std::ranges::range_value_t<decltype(rhs)>>)
{
    for (gsl::index i = 0;
         auto&& value : std::forward<decltype(rhs)>(rhs)) {
        lhs[i] = std::forward<decltype(value)>(value);
        ++i;
    }
    return lhs;
}

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
/// e.g. VectorAssign<double, 3>(u, v); VectorAssign<double, 3>(u, {x, y, z});
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
decltype(auto) VectorAssign(Concept::NumericVectorAny auto& lhs, const Concept::InputVectorAny auto& rhs)
    requires(not std::assignable_from<decltype(lhs), decltype(rhs)> and
             not std::ranges::input_range<decltype(rhs)>)
{
    for (gsl::index i = 0; i < ToSigned(VectorDimension<std::remove_cvref_t<decltype(lhs)>>); ++i) {
        lhs[i] = rhs[i];
    }
    return lhs;
}

} // namespace MACE::inline Utility
