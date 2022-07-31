#pragma once

#include <concepts>
#include <utility>

namespace MACE::Utility {

/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(const AATuple<AElement...>&& tuple, AFunctor&& func);
/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(AATuple<AElement...>&& tuple, AFunctor&& func);
/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(const AATuple<AElement...>& tuple, AFunctor&& func);
/// @brief Traverses a std::tuple or its derived class.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(AATuple<AElement...>& tuple, AFunctor&& func);

} // namespace MACE::Utility

#include "MACE/Utility/TupleForEach.inl"
