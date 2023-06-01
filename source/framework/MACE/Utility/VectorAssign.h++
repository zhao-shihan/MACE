#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Concept/Indirectable.h++"
#include "MACE/Concept/InputVector.h++"
#include "MACE/Concept/NumericVector.h++"
#include "MACE/Utility/ToSigned.h++"
#include "MACE/Utility/VectorDimension.h++"
#include "MACE/Utility/VectorValueType.h++"

#include "gsl/gsl"

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace MACE::inline Utility {

/// @brief Assign something to a vector. If lhs = rhs is well-formed, assign
/// with operator=, else assign element by element.
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
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
decltype(auto) VectorAssign(Concept::NumericVectorAny auto& lhs, std::ranges::input_range auto&& rhs)
    requires(not std::assignable_from<decltype(lhs), decltype(rhs)> and
             std::assignable_from<VectorValueType<std::decay_t<decltype(lhs)>>&, std::ranges::range_value_t<decltype(rhs)>>)
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
/// @param lhs The vector at left-hand side.
/// @param rhs Something at right hand side.
/// @return If lhs = rhs is well-formed, returns lhs = rhs, else returns the
/// lvalue reference to lhs.
decltype(auto) VectorAssign(Concept::NumericVectorAny auto& lhs, const Concept::InputVectorAny auto& rhs)
    requires(not std::assignable_from<decltype(lhs), decltype(rhs)> and
             not std::ranges::input_range<decltype(rhs)>)
{
    for (gsl::index i = 0; i < ToSigned(VectorDimension<std::decay_t<decltype(lhs)>>); ++i) {
        lhs[i] = rhs[i];
    }
    return lhs;
}

inline namespace VectorAssignOperator {

decltype(auto) operator<<=(Concept::NumericVectorAny auto& lhs, auto&& rhs)
    requires requires { VectorAssign(lhs, std::forward<decltype(rhs)>(rhs)); }
{
    return VectorAssign(lhs, std::forward<decltype(rhs)>(rhs));
}

} // namespace VectorAssignOperator

} // namespace MACE::inline Utility
