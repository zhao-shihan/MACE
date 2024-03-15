#pragma once

#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_like.h++"

#include "gsl/gsl"

#include <functional>
#include <utility>

namespace MACE::inline Extension::stdx {

namespace internal {

template<typename F, typename T, gsl::index... Is>
    requires tuple_like<std::decay_t<T>>
constexpr auto apply(F&& f, T&& t, gslx::index_sequence<Is...>) noexcept(
    noexcept(std::invoke(std::forward<F>(f), get<Is>(std::forward<T>(t))...)))
    -> decltype(auto) {
    return std::invoke(std::forward<F>(f), get<Is>(std::forward<T>(t))...);
}

} // namespace internal

template<typename F, typename T>
    requires tuple_like<std::decay_t<T>>
constexpr auto apply(F&& f, T&& t) noexcept(
    noexcept(internal::apply(std::forward<F>(f), std::forward<T>(t), gslx::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{})))
    -> decltype(auto) {
    return internal::apply(std::forward<F>(f), std::forward<T>(t), gslx::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{});
}

} // namespace MACE::inline Extension::stdx
