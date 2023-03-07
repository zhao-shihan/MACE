#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/AssignVector.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"

#include <concepts>
#include <type_traits>
#include <utility>

namespace MACE::Utility {

template<class T, std::size_t N>
    requires Concept::NumericVectorAny<T, N>
[[nodiscard]] T VectorCast(T&& src) {
    return src;
}

template<class T, std::size_t N>
    requires Concept::NumericVectorAny<T, N>
[[nodiscard]] T VectorCast(std::convertible_to<T> auto&& src) {
    return src;
}

template<class T, std::size_t N>
    requires Concept::NumericVectorAny<T, N>
[[nodiscard]] T VectorCast(auto&& src)
    requires(not std::convertible_to<decltype(src), T>)
{
    T dst;
    AssignVector<ValueTypeOf<T>, N>(dst, std::forward<decltype(src)>(src));
    return dst;
}

template<class T, std::size_t N>
    requires Concept::NumericVectorAny<T, N>
[[nodiscard]] T VectorCast(auto&&... args)
    requires(std::same_as<std::common_type_t<T, decltype(args)...>, T> and
             sizeof...(args) == N)
{
    return {std::forward<decltype(args)>(args)...};
}

} // namespace MACE::Utility
