#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <concepts>
#include <type_traits>
#include <utility>

namespace MACE::inline Utility {

template<Concept::NumericVectorAny T>
[[nodiscard]] T VectorCast(std::convertible_to<T> auto&& src) {
    return std::forward<decltype(src)>(src);
}

template<Concept::NumericVectorAny T>
[[nodiscard]] T VectorCast(auto&& src)
    requires(not std::convertible_to<decltype(src), T>)
{
    T dst;
    VectorAssign(dst, std::forward<decltype(src)>(src));
    return dst;
}

} // namespace MACE::inline Utility
