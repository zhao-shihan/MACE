#pragma once

#include <type_traits>

namespace MACE::Concept {

namespace internal {

template<template<typename...> class, typename>
struct IsTemplateOf : std::false_type {};

template<template<typename...> class ATemplate, typename... Args>
struct IsTemplateOf<ATemplate, ATemplate<Args...>> : std::true_type {};

} // namespace internal

template<class T, template<typename...> class ATemplate>
concept InstantiatedFrom = internal::IsTemplateOf<ATemplate, T>::value;

} // namespace MACE::Concept
