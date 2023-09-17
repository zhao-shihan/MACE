#pragma once

#include "MACE/Data/Model/Field.h++"

#include <type_traits>

namespace MACE::Data::inline Model {

namespace internal {

template<template<typename, gsl::index> typename, typename>
struct IsSignedFieldTemplateOf
    : std::false_type {};

template<template<typename, gsl::index> typename ASignedField, typename AFieldSet, gsl::index I>
struct IsSignedFieldTemplateOf<ASignedField, ASignedField<AFieldSet, I>>
    : std::true_type {};

} // namespace internal

template<typename F>
concept SignedField = requires {
    requires internal::IsSignedFieldTemplateOf<Field<typename F::Type>::template Signed, F>::value;
    typename F::Type;
};

} // namespace MACE::Data::inline Model
