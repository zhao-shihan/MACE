#pragma once

#include "MACE/Data/Model/Field.h++"

#include <type_traits>

namespace MACE::Data::inline Model {

namespace internal {

template<template<typename, gsl::index> typename, typename>
struct IsNamedFieldTemplateOf
    : std::false_type {};

template<template<typename, gsl::index> typename ANamedField, typename AFieldSet, gsl::index I>
struct IsNamedFieldTemplateOf<ANamedField, ANamedField<AFieldSet, I>>
    : std::true_type {};

} // namespace internal

template<typename F>
concept NamedField = requires {
    requires internal::IsNamedFieldTemplateOf<Field<typename F::Type>::template Named, F>::value;
    typename F::Type;
    requires std::is_trivially_destructible_v<F>;
};

} // namespace MACE::Data::inline Model
