#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/GeneralNumericVector.hxx"

#include "gsl/gsl"

#include <type_traits>
#include <utility>

namespace MACE::Utility {

namespace internal {

template<class T>
struct ValueTypeOf {};

template<class T>
    requires requires { typename T::value_type; }
struct ValueTypeOf<T> {
    using Type = typename T::value_type;
};

template<Concept::GeneralNumericVectorAny T>
    requires(not requires { typename T::value_type; })
struct ValueTypeOf<T> {
    using Type = std::remove_reference_t<decltype(std::declval<T&>()[std::declval<gsl::index>()])>;
};

} // namespace internal

template<class T>
using ValueTypeOf = typename internal::ValueTypeOf<T>::Type;

} // namespace MACE::Utility
