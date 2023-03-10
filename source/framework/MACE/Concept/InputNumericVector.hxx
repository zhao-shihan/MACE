#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/Subscriptable.hxx"

#include <concepts>
#include <cstddef>
#include <limits>

namespace MACE::Concept {

template<class T, typename F, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept InputNumericVector =
    requires {
        requires(N >= 2);
        requires Arithmetic<F>;
        requires(std::default_initializable<T> and WeaklySubscriptableTo<T, F>) or
                    ((std::is_pointer_v<T> or std::is_array_v<T>) and WeaklySubscriptableToMaybeConst<T, F>);
    };

template<class T, typename F>
concept InputNumericVector2 = InputNumericVector<T, F, 2>;
template<class T, typename F>
concept InputNumericVector3 = InputNumericVector<T, F, 3>;
template<class T, typename F>
concept InputNumericVector4 = InputNumericVector<T, F, 4>;
template<class T>
concept InputNumericVector2F = InputNumericVector2<T, float>;
template<class T>
concept InputNumericVector3F = InputNumericVector3<T, float>;
template<class T>
concept InputNumericVector4F = InputNumericVector4<T, float>;
template<class T>
concept InputNumericVector2D = InputNumericVector2<T, double>;
template<class T>
concept InputNumericVector3D = InputNumericVector3<T, double>;
template<class T>
concept InputNumericVector4D = InputNumericVector4<T, double>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept InputNumericVectorIntegral =
    requires(T v, gsl::index i) {
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
        requires InputNumericVector<T, std::remove_reference_t<decltype(v[i])>, N>;
    };

template<class T>
concept InputNumericVector2Integral = InputNumericVectorIntegral<T, 2>;
template<class T>
concept InputNumericVector3Integral = InputNumericVectorIntegral<T, 3>;
template<class T>
concept InputNumericVector4Integral = InputNumericVectorIntegral<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept InputNumericVectorFloatingPoint =
    requires(T v, gsl::index i) {
        requires(WeaklySubscriptableTo<T, float> or
                 WeaklySubscriptableTo<T, double> or
                 WeaklySubscriptableTo<T, long double>);
        requires InputNumericVector<T, std::remove_reference_t<decltype(v[i])>, N>;
    };

template<class T>
concept InputNumericVector2FloatingPoint = InputNumericVectorFloatingPoint<T, 2>;
template<class T>
concept InputNumericVector3FloatingPoint = InputNumericVectorFloatingPoint<T, 3>;
template<class T>
concept InputNumericVector4FloatingPoint = InputNumericVectorFloatingPoint<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept InputNumericVectorAny =
    InputNumericVectorIntegral<T, N> or
    InputNumericVectorFloatingPoint<T, N>;

template<class T>
concept InputNumericVector2Any = InputNumericVectorAny<T, 2>;
template<class T>
concept InputNumericVector3Any = InputNumericVectorAny<T, 3>;
template<class T>
concept InputNumericVector4Any = InputNumericVectorAny<T, 4>;

} // namespace MACE::Concept
