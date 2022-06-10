#pragma once

#include <concepts>
#include <utility>

namespace MACE::Utility {

/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(const TupleTT<ElementT...>& tuple, FunctorT&& func);
/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(TupleTT<ElementT...>& tuple, FunctorT&& func);
/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(TupleTT<ElementT...>&& tuple, FunctorT&& func);

} // namespace MACE::Utility

#include "MACE/Utility/TupleForEach.ixx"
