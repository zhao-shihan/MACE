/// Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that the arg is a tuple.

#pragma once

#include <utility>

namespace MACE::Utility {

template<template<typename... T> class Tuple_tt, class Functor_t, typename... Element_t>
requires std::derived_from<Tuple_tt<Element_t...>, std::tuple<Element_t...>>
class TupleForEachImpl {
    using TupleSize = std::integral_constant<std::size_t, sizeof...(Element_t)>;
    using Tuple_t = Tuple_tt<Element_t...>;

    template<typename TupleCVRef_t, std::size_t... Index>
    requires std::same_as<std::remove_cvref_t<TupleCVRef_t>, Tuple_t>
    constexpr void Impl(TupleCVRef_t&& tuple, Functor_t&& func, std::index_sequence<Index...>&&) const {
        (func(std::get<Index>(std::forward<TupleCVRef_t>(tuple))), ...);
    }

public:
    template<typename TupleCVRef_t>
    requires std::same_as<std::remove_cvref_t<TupleCVRef_t>, Tuple_t>
    constexpr void operator()(TupleCVRef_t&& tuple, Functor_t&& func) const {
        Impl(std::forward<TupleCVRef_t>(tuple), std::forward<Functor_t>(func), std::make_index_sequence<TupleSize::value>());
    }
};

/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class Tuple_tt, class Functor_t, typename... Element_t>
constexpr void TupleForEach(const Tuple_tt<Element_t...>& tuple, Functor_t&& func) {
    TupleForEachImpl<Tuple_tt, Functor_t, Element_t...>()(tuple, std::forward<Functor_t>(func));
}

/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class Tuple_tt, class Functor_t, typename... Element_t>
constexpr void TupleForEach(Tuple_tt<Element_t...>& tuple, Functor_t&& func) {
    TupleForEachImpl<Tuple_tt, Functor_t, Element_t...>()(tuple, std::forward<Functor_t>(func));
}

/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class Tuple_tt, class Functor_t, typename... Element_t>
constexpr void TupleForEach(Tuple_tt<Element_t...>&& tuple, Functor_t&& func) {
    TupleForEachImpl<Tuple_tt, Functor_t, Element_t...>()(tuple, std::forward<Functor_t>(func));
}

} // namespace MACE::Utility
