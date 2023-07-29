#pragma once

#include "MACE/Data/Model/Field/BasicField.h++"

namespace MACE::Data::inline Model::inline Field {

namespace detail {

template<template<typename, gsl::index> typename, typename>
struct IsNamedFieldTemplateOf
    : std::false_type {};

template<template<typename, gsl::index> typename ANamedField, typename AFieldSet, gsl::index I>
struct IsNamedFieldTemplateOf<ANamedField, ANamedField<AFieldSet, I>>
    : std::true_type {};

} // namespace internal

template<typename F>
concept NamedField = requires {
    typename F::Type;
    requires detail::IsNamedFieldTemplateOf<BasicField<typename F::Type>::template Named, F>::value;
};

} // namespace MACE::Data::inline Field
