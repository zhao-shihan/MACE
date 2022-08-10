#pragma once

#include "MACE/Utility/Concept/FundamentalType.hxx"
#include "MACE/Utility/Concept/IsPointer.hxx"
#include "MACE/Utility/Concept/Subscriptable.hxx"

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::Utility::Concept {

template<class T, typename F, std::size_t S>
concept NumericVector = requires { // clang-format off
    requires S > 0; // clang-format on
    requires ArithmeticExcludeBool<F>;
}
and(IsPointerOfMaybeConst<std::decay_t<T>, F> or
    requires {
        requires SubscriptableTo<std::remove_const_t<T>, F&>;
        requires SubscriptableTo<const T&, const F&> or SubscriptableTo<const T&, F>;
    });

template<class T>
concept NumericVector2D = NumericVector<T, double, 2>;

template<class T>
concept NumericVector3D = NumericVector<T, double, 3>;

template<class T>
concept NumericVector4D = NumericVector<T, double, 4>;

template<class T>
concept NumericVector2F = NumericVector<T, float, 2>;

template<class T>
concept NumericVector3F = NumericVector<T, float, 3>;

template<class T>
concept NumericVector4F = NumericVector<T, float, 4>;

} // namespace MACE::Utility::Concept
