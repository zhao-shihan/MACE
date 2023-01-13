#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/Subscriptable.hxx"

#include <concepts>
#include <cstddef>
#include <limits>

namespace MACE::Concept {

template<class T, typename F, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept GeneralNumericVector = requires {
    requires(N >= 2);
    requires Arithmetic<F>;
    requires(std::default_initializable<T> and WeaklySubscriptableTo<T, F>) or
        ((std::is_pointer_v<T> or std::is_array_v<T>)and WeaklySubscriptableToMaybeConst<T, F>);
};

template<class T, typename F>
concept GeneralNumericVector2 = GeneralNumericVector<T, F, 2>;
template<class T, typename F>
concept GeneralNumericVector3 = GeneralNumericVector<T, F, 3>;
template<class T, typename F>
concept GeneralNumericVector4 = GeneralNumericVector<T, F, 4>;
template<class T>
concept GeneralNumericVector2F = GeneralNumericVector2<T, float>;
template<class T>
concept GeneralNumericVector3F = GeneralNumericVector3<T, float>;
template<class T>
concept GeneralNumericVector4F = GeneralNumericVector4<T, float>;
template<class T>
concept GeneralNumericVector2D = GeneralNumericVector2<T, double>;
template<class T>
concept GeneralNumericVector3D = GeneralNumericVector3<T, double>;
template<class T>
concept GeneralNumericVector4D = GeneralNumericVector4<T, double>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept GeneralNumericVectorIntegral = requires(T v, gsl::index i) {
    requires(WeaklySubscriptableTo<T, bool> or
             WeaklySubscriptableTo<T, signed char> or
             WeaklySubscriptableTo<T, unsigned char> or
             WeaklySubscriptableTo<T, char> or
             WeaklySubscriptableTo<T, char8_t> or
             WeaklySubscriptableTo<T, char16_t> or
             WeaklySubscriptableTo<T, char32_t> or
             WeaklySubscriptableTo<T, wchar_t> or
             WeaklySubscriptableTo<T, short> or
             WeaklySubscriptableTo<T, int> or
             WeaklySubscriptableTo<T, long> or
             WeaklySubscriptableTo<T, long long> or
             WeaklySubscriptableTo<T, unsigned short> or
             WeaklySubscriptableTo<T, unsigned int> or
             WeaklySubscriptableTo<T, unsigned long> or
             WeaklySubscriptableTo<T, unsigned long long>);
    requires GeneralNumericVector<T, std::remove_reference_t<decltype(v[i])>, N>;
};

template<class T>
concept GeneralNumericVector2Integral = GeneralNumericVectorIntegral<T, 2>;
template<class T>
concept GeneralNumericVector3Integral = GeneralNumericVectorIntegral<T, 3>;
template<class T>
concept GeneralNumericVector4Integral = GeneralNumericVectorIntegral<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept GeneralNumericVectorFloatingPoint = requires(T v, gsl::index i) {
    requires(WeaklySubscriptableTo<T, float> or
             WeaklySubscriptableTo<T, double> or
             WeaklySubscriptableTo<T, long double>);
    requires GeneralNumericVector<T, std::remove_reference_t<decltype(v[i])>, N>;
};

template<class T>
concept GeneralNumericVector2FloatingPoint = GeneralNumericVectorFloatingPoint<T, 2>;
template<class T>
concept GeneralNumericVector3FloatingPoint = GeneralNumericVectorFloatingPoint<T, 3>;
template<class T>
concept GeneralNumericVector4FloatingPoint = GeneralNumericVectorFloatingPoint<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept GeneralNumericVectorAny =
    GeneralNumericVectorIntegral<T, N> or
    GeneralNumericVectorFloatingPoint<T, N>;

template<class T>
concept GeneralNumericVector2Any = GeneralNumericVectorAny<T, 2>;
template<class T>
concept GeneralNumericVector3Any = GeneralNumericVectorAny<T, 3>;
template<class T>
concept GeneralNumericVector4Any = GeneralNumericVectorAny<T, 4>;

} // namespace MACE::Concept
