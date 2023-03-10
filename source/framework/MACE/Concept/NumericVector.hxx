#pragma once

#include "MACE/Concept/InputNumericVector.hxx"
#include "MACE/Concept/Subscriptable.hxx"

#include <array>
#include <concepts>
#include <cstddef>
#include <limits>
#include <type_traits>

namespace MACE::Concept {

namespace internal {

template<class T>
struct ListInitialization {
    static constexpr auto Direct = [](auto... x) {
        [[maybe_unused]] T v{x...};
        ::delete ::new T{x...};
        return T{x...};
    };

    static constexpr auto Copy = [](auto... x) -> T {
        T v = {x...};
        v = {x...};
        return {x...};
    };
};

} // namespace internal

template<class T, typename F, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept NumericVector =
    requires {
        requires InputNumericVector<T, F, N>;
        requires std::is_standard_layout_v<T>;
        requires std::is_class_v<T>;
        requires std::regular<T>;
        requires(N == std::numeric_limits<std::size_t>::max() or
                 requires(std::array<F, N> u) {
                     requires sizeof(T) == N * sizeof(F);
                     std::apply(internal::ListInitialization<T>::Direct, u);
                     std::apply(internal::ListInitialization<T>::Copy, u);
                 });
        requires SubscriptableTo<T, F&>;
        requires(SubscriptableTo<std::add_const_t<T>, const F&> or
                 SubscriptableTo<std::add_const_t<T>, F>);
    };

template<class T, typename F>
concept NumericVector2 = NumericVector<T, F, 2>;
template<class T, typename F>
concept NumericVector3 = NumericVector<T, F, 3>;
template<class T, typename F>
concept NumericVector4 = NumericVector<T, F, 4>;
template<class T>
concept NumericVector2F = NumericVector2<T, float>;
template<class T>
concept NumericVector3F = NumericVector3<T, float>;
template<class T>
concept NumericVector4F = NumericVector4<T, float>;
template<class T>
concept NumericVector2D = NumericVector2<T, double>;
template<class T>
concept NumericVector3D = NumericVector3<T, double>;
template<class T>
concept NumericVector4D = NumericVector4<T, double>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept NumericVectorIntegral =
    NumericVector<T, bool, N> or
    NumericVector<T, signed char, N> or
    NumericVector<T, unsigned char, N> or
    NumericVector<T, char, N> or
    NumericVector<T, char8_t, N> or
    NumericVector<T, char16_t, N> or
    NumericVector<T, char32_t, N> or
    NumericVector<T, wchar_t, N> or
    NumericVector<T, short, N> or
    NumericVector<T, int, N> or
    NumericVector<T, long, N> or
    NumericVector<T, long long, N> or
    NumericVector<T, unsigned short, N> or
    NumericVector<T, unsigned int, N> or
    NumericVector<T, unsigned long, N> or
    NumericVector<T, unsigned long long, N>;

template<class T>
concept NumericVector2Integral = NumericVectorIntegral<T, 2>;
template<class T>
concept NumericVector3Integral = NumericVectorIntegral<T, 3>;
template<class T>
concept NumericVector4Integral = NumericVectorIntegral<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept NumericVectorFloatingPoint =
    NumericVector<T, float, N> or
    NumericVector<T, double, N> or
    NumericVector<T, long double, N>;

template<class T>
concept NumericVector2FloatingPoint = NumericVectorFloatingPoint<T, 2>;
template<class T>
concept NumericVector3FloatingPoint = NumericVectorFloatingPoint<T, 3>;
template<class T>
concept NumericVector4FloatingPoint = NumericVectorFloatingPoint<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept NumericVectorAny =
    NumericVectorIntegral<T, N> or
    NumericVectorFloatingPoint<T, N>;

template<class T>
concept NumericVector2Any = NumericVectorAny<T, 2>;
template<class T>
concept NumericVector3Any = NumericVectorAny<T, 3>;
template<class T>
concept NumericVector4Any = NumericVectorAny<T, 4>;

} // namespace MACE::Concept
