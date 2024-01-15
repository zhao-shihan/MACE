#pragma once

#include "MACE/Extension/stdx/tuple_like.h++"

#include <tuple>

namespace MACE::inline Extension::stdx {

namespace internal {

template<tuple_like, std::size_t, std::size_t, tuple_like>
struct to_std_tuple_helper;

template<tuple_like T, std::size_t I, std::size_t N, typename... Ts>
struct to_std_tuple_helper<T, I, N,
                           std::tuple<Ts...>>
    : to_std_tuple_helper<T, I + 1, N,
                          std::tuple<Ts..., std::tuple_element_t<I, T>>> {};

template<tuple_like T, std::size_t N, typename... Ts>
struct to_std_tuple_helper<T, N, N,
                           std::tuple<Ts...>> {
    using type = std::tuple<Ts...>;
};

} // namespace internal

template<tuple_like T>
struct to_std_tuple
    : internal::to_std_tuple_helper<T, 0, std::tuple_size_v<T>,
                                    std::tuple<>> {};

template<tuple_like T>
using to_std_tuple_t = typename to_std_tuple<T>::type;

} // namespace MACE::inline Extension::stdx
