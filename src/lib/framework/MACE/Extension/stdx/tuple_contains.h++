#pragma once

#include "MACE/Extension/stdx/tuple_count.h++"
#include "MACE/Extension/stdx/tuple_like.h++"

#include <type_traits>

namespace MACE::inline Extension::stdx {

template<tuple_like T, typename U>
struct tuple_contains
    : std::conditional_t<tuple_count_v<T, U> >= 1,
                         std::true_type,
                         std::false_type> {};

template<tuple_like T, typename U>
inline constexpr auto tuple_contains_v = tuple_contains<T, U>::value;

template<tuple_like T, typename U>
struct tuple_contains_unique
    : std::conditional_t<tuple_count_v<T, U> == 1,
                         std::true_type,
                         std::false_type> {};

template<tuple_like T, typename U>
inline constexpr auto tuple_contains_unique_v = tuple_contains_unique<T, U>::value;

} // namespace MACE::inline Extension::stdx
