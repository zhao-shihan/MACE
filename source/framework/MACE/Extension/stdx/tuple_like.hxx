#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace MACE::inline Extension::stdx {

namespace internal {

template<class T, std::size_t N>
concept has_tuple_element =
    requires(T t) {
        typename std::tuple_element_t<N, std::remove_const_t<T>>;
        { std::get<N>(t) } -> std::convertible_to<const std::tuple_element_t<N, T>&>;
    };

} // namespace internal

template<class T>
concept tuple_like =
    not std::is_reference_v<T> and
    requires(T t) {
        typename std::tuple_size<T>::type;
        requires std::derived_from<std::tuple_size<T>,
                                   std::integral_constant<std::size_t, std::tuple_size_v<T>>>;
    } and []<std::size_t... N>(std::index_sequence<N...>) {
        return (... and internal::has_tuple_element<T, N>);
    }(std::make_index_sequence<std::tuple_size_v<T>>());

template<class T>
concept pair_like = tuple_like<T> and std::tuple_size_v<T> == 2;

} // namespace MACE::inline Extension::stdx
