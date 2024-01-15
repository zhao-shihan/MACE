#pragma once

#include <type_traits>

namespace MACE::Concept {

// Work around LLVM issue #57142 (https://github.com/llvm/llvm-project/issues/57142)
// #if not defined __clang__ or __clang_major__ <= 12

namespace internal {

template<template<typename...> typename, typename>
struct IsTemplateOf
    : std::false_type {};

template<template<typename...> typename ATemplate, typename... Args>
struct IsTemplateOf<ATemplate, ATemplate<Args...>>
    : std::true_type {};

} // namespace internal

template<typename T, template<typename...> typename ATemplate>
concept InstantiatedFrom = internal::IsTemplateOf<ATemplate, T>::value;

// #else

// template<typename T, template<typename...> typename>
// concept InstantiatedFrom = std::is_class_v<T>;

// #endif

} // namespace MACE::Concept
