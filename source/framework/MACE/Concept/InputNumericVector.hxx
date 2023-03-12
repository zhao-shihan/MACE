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
        requires(std::is_class_v<std::remove_cvref_t<T>> and
                 std::default_initializable<std::remove_cvref_t<T>>) or
                    (std::is_pointer_v<std::remove_cvref_t<T>> or
                     std::is_array_v<std::remove_cvref_t<T>>);
        requires SubscriptableToMaybeConstReferenced<T, F>;
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
        requires(SubscriptableToMaybeReferenced<T, bool> or
                 SubscriptableToMaybeReferenced<T, signed char> or
                 SubscriptableToMaybeReferenced<T, unsigned char> or
                 SubscriptableToMaybeReferenced<T, char> or
                 SubscriptableToMaybeReferenced<T, char8_t> or
                 SubscriptableToMaybeReferenced<T, char16_t> or
                 SubscriptableToMaybeReferenced<T, char32_t> or
                 SubscriptableToMaybeReferenced<T, wchar_t> or
                 SubscriptableToMaybeReferenced<T, short> or
                 SubscriptableToMaybeReferenced<T, int> or
                 SubscriptableToMaybeReferenced<T, long> or
                 SubscriptableToMaybeReferenced<T, long long> or
                 SubscriptableToMaybeReferenced<T, unsigned short> or
                 SubscriptableToMaybeReferenced<T, unsigned int> or
                 SubscriptableToMaybeReferenced<T, unsigned long> or
                 SubscriptableToMaybeReferenced<T, unsigned long long>);
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
        requires(SubscriptableToMaybeReferenced<T, float> or
                 SubscriptableToMaybeReferenced<T, double> or
                 SubscriptableToMaybeReferenced<T, long double>);
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
