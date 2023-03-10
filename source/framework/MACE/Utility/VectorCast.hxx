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

template<Concept::NumericVectorAny<2> T>
[[nodiscard]] T Vector2Cast(auto&&... args)
    requires(sizeof...(args) == 1 or
             sizeof...(args) == 2)
{
    return VectorCast<T, 2>(std::forward<decltype(args)>(args)...);
}

template<Concept::NumericVectorAny<3> T>
[[nodiscard]] T Vector3Cast(auto&&... args)
    requires(sizeof...(args) == 1 or
             sizeof...(args) == 3)
{
    return VectorCast<T, 3>(std::forward<decltype(args)>(args)...);
}

template<Concept::NumericVectorAny<4> T>
[[nodiscard]] T Vector4Cast(auto&&... args)
    requires(sizeof...(args) == 1 or
             sizeof...(args) == 4)
{
    return VectorCast<T, 4>(std::forward<decltype(args)>(args)...);
}

} // namespace MACE::Utility
