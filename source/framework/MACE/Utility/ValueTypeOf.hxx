#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/InputNumericVector.hxx"

#include "gsl/gsl"

#include <ranges>
#include <type_traits>
#include <utility>

namespace MACE::inline Utility {

namespace internal {

template<class T>
struct ValueTypeOfImpl {};

template<class T>
    requires requires { typename T::value_type; }
struct ValueTypeOfImpl<T> {
    using Type = typename T::value_type;
};

template<std::ranges::input_range T>
    requires(not requires { typename T::value_type; })
struct ValueTypeOfImpl<T> {
    using Type = std::remove_reference_t<decltype(*std::declval<std::ranges::iterator_t<T>>())>;
};

template<Concept::InputNumericVectorAny T>
    requires(not requires { typename T::value_type; } and
             not std::ranges::input_range<T>)
struct ValueTypeOfImpl<T> {
    using Type = std::remove_reference_t<decltype(std::declval<T&>()[std::declval<gsl::index>()])>;
};

} // namespace internal

template<class T>
using ValueTypeOf = typename internal::ValueTypeOfImpl<T>::Type;

} // namespace MACE::inline Utility
