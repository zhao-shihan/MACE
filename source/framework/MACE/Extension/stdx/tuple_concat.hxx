#pragma once

#include "MACE/Extension/stdx/tuple_like.hxx"

#include <tuple>
#include <utility>

namespace MACE::inline Extension::stdx {

template<typename... Ts>
    requires(... and tuple_like<Ts>)
struct tuple_concat {
    using type = decltype(std::tuple_cat(std::declval<Ts>()...));
};

template<typename... Ts>
using tuple_concat_t = typename tuple_concat<Ts...>::type;

} // namespace MACE::inline Extension::stdx
