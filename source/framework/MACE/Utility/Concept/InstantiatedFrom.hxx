#pragma once

#include <type_traits>

namespace MACE::Utility::Concept {

namespace Internal {

template<template<typename...> class, typename>
struct IsTemplateOf : std::false_type {};

template<template<typename...> class ATemplate, typename... Args>
struct IsTemplateOf<ATemplate, ATemplate<Args...>> : std::true_type {};

} // namespace Internal

template<class T, template<typename...> class ATemplate>
concept InstantiatedFrom = Internal::IsTemplateOf<ATemplate, T>::value;

} // namespace MACE::Utility::Concept
