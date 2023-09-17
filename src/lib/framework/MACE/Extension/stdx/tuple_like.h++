#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace MACE::inline Extension::stdx {

namespace internal {

template<typename T, std::size_t I>
concept has_tuple_element_and_get =
    requires(T t) {
        typename std::tuple_element_t<I, std::remove_const_t<T>>;
        { std::get<I>(t) } -> std::convertible_to<const std::tuple_element_t<I, T>&>;
    };

} // namespace internal

template<typename T>
concept tuple_like =
    requires {
        requires not std::is_reference_v<T>;
        typename std::tuple_size<T>::type;
        requires std::derived_from<std::tuple_size<T>,
                                   std::integral_constant<std::size_t, std::tuple_size_v<T>>>;
        requires
            []<std::size_t... Is>(std::index_sequence<Is...>) {
                return (... and internal::has_tuple_element_and_get<T, Is>);
            }(std::make_index_sequence<std::tuple_size_v<T>>());
    };

} // namespace MACE::inline Extension::stdx
