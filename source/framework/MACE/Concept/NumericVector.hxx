#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/Pointer.hxx"
#include "MACE/Concept/Subscriptable.hxx"

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::Concept {

template<class T, typename F, std::size_t N>
concept WeakNumericVector = requires {
    requires(N > 0);
    requires ArithmeticExcludeBool<F>;
    requires WeaklySubscriptableToMaybeConst<T, F>;
};

template<class T>
concept WeakNumericVector2D = WeakNumericVector<T, double, 2>;
template<class T>
concept WeakNumericVector3D = WeakNumericVector<T, double, 3>;
template<class T>
concept WeakNumericVector4D = WeakNumericVector<T, double, 4>;
template<class T>
concept WeakNumericVector2F = WeakNumericVector<T, float, 2>;
template<class T>
concept WeakNumericVector3F = WeakNumericVector<T, float, 3>;
template<class T>
concept WeakNumericVector4F = WeakNumericVector<T, float, 4>;

template<class T, typename F, std::size_t N>
concept NumericVector = requires {
    requires WeakNumericVector<T, F, N>;
    requires std::is_class_v<T>;
    requires std::regular<std::remove_const_t<T>>;
};

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

} // namespace MACE::Concept
