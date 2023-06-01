#pragma once

#include "MACE/Extension/stdx/to_std_tuple.h++"
#include "MACE/Extension/stdx/tuple_like.h++"

#include <tuple>

namespace MACE::inline Extension::stdx {

namespace internal {

template<tuple_like...>
struct std_tuple_concat;

template<>
struct std_tuple_concat<> {
    using type = std::tuple<>;
};

template<typename... Ts>
struct std_tuple_concat<std::tuple<Ts...>> {
    using type = std::tuple<Ts...>;
};

template<typename... Ts, typename... Us, typename... Vs>
struct std_tuple_concat<std::tuple<Ts...>, std::tuple<Us...>, Vs...>
    : std_tuple_concat<std::tuple<Ts..., Us...>, Vs...> {};

template<tuple_like... Ts>
using std_tuple_concat_t = typename std_tuple_concat<Ts...>::type;

} // namespace internal

template<tuple_like... Ts>
struct tuple_concat
    : internal::std_tuple_concat<to_std_tuple_t<Ts>...> {};

template<tuple_like... Ts>
using tuple_concat_t = typename tuple_concat<Ts...>::type;

} // namespace MACE::inline Extension::stdx
