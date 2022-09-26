#pragma once

#include <type_traits>

namespace MACE::Concept {

// Work around LLVM issue #57142 (https://github.com/llvm/llvm-project/issues/57142)
#if defined __clang__ and __clang_major__ <= 12

namespace internal {

template<template<typename...> class, typename>
struct IsTemplateOf : std::false_type {};

template<template<typename...> class ATemplate, typename... Args>
struct IsTemplateOf<ATemplate, ATemplate<Args...>> : std::true_type {};

} // namespace internal

template<class T, template<typename...> class ATemplate>
concept InstantiatedFrom = internal::IsTemplateOf<ATemplate, T>::value;

#else

template<class T, template<typename...> class>
concept InstantiatedFrom = std::is_class_v<T>;

#endif

} // namespace MACE::Concept
