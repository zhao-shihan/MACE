#pragma once

#include "MACE/Compatibility/CLHEPDefectFix/Hep2VectorDivisionAssignment.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/VectorValueType.hxx"

#include <concepts>
#include <cstddef>
#include <limits>
#include <type_traits>

namespace MACE::Concept {

namespace internal {

template<class T>
concept ExtraRequirementsForMathVector =
    requires(T u, const T v, const T w, const VectorValueType<T> c) {
        { u += v } -> std::same_as<T&>;
        { u -= v } -> std::same_as<T&>;
        { u *= c } -> std::same_as<T&>;
        { u /= c } -> std::same_as<T&>;
        { -v } -> std::convertible_to<T>;
        { v + w } -> std::convertible_to<T>;
        { v - w } -> std::convertible_to<T>;
        { c* v } -> std::convertible_to<T>;
        { v* c } -> std::convertible_to<T>;
        { v / c } -> std::convertible_to<T>;
    };

} // namespace internal

template<class T, typename F, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept MathVector =
    requires {
        requires NumericVector<T, F, N>;
        requires internal::ExtraRequirementsForMathVector<T>;
    };

template<class T, typename F>
concept MathVector2 = MathVector<T, F, 2>;
template<class T, typename F>
concept MathVector3 = MathVector<T, F, 3>;
template<class T, typename F>
concept MathVector4 = MathVector<T, F, 4>;
template<class T>
concept MathVector2F = MathVector2<T, float>;
template<class T>
concept MathVector3F = MathVector3<T, float>;
template<class T>
concept MathVector4F = MathVector4<T, float>;
template<class T>
concept MathVector2D = MathVector2<T, double>;
template<class T>
concept MathVector3D = MathVector3<T, double>;
template<class T>
concept MathVector4D = MathVector4<T, double>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept MathVectorIntegral =
    requires {
        requires NumericVectorIntegral<T, N>;
        requires internal::ExtraRequirementsForMathVector<T>;
    };

template<class T>
concept MathVector2Integral = MathVectorIntegral<T, 2>;
template<class T>
concept MathVector3Integral = MathVectorIntegral<T, 3>;
template<class T>
concept MathVector4Integral = MathVectorIntegral<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept MathVectorFloatingPoint =
    requires {
        requires NumericVectorFloatingPoint<T, N>;
        requires internal::ExtraRequirementsForMathVector<T>;
    };

template<class T>
concept MathVector2FloatingPoint = MathVectorFloatingPoint<T, 2>;
template<class T>
concept MathVector3FloatingPoint = MathVectorFloatingPoint<T, 3>;
template<class T>
concept MathVector4FloatingPoint = MathVectorFloatingPoint<T, 4>;

template<class T, std::size_t N = std::numeric_limits<std::size_t>::max()>
concept MathVectorAny =
    requires {
        requires NumericVectorAny<T, N>;
        requires internal::ExtraRequirementsForMathVector<T>;
    };

template<class T>
concept MathVector2Any = MathVectorAny<T, 2>;
template<class T>
concept MathVector3Any = MathVectorAny<T, 3>;
template<class T>
concept MathVector4Any = MathVectorAny<T, 4>;

} // namespace MACE::Concept
