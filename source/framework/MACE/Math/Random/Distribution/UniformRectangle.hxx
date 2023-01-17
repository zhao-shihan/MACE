#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Math/Random/Distribution/Joint.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"

#include <array>
#include <concepts>
#include <iomanip>
#include <type_traits>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector2Any T, template<class> class AUniformRectangle, template<typename> class AUniform>
class BasicUniformRectangleParameter final : public JointParameterInterface<BasicUniformRectangleParameter<T, AUniformRectangle, AUniform>,
                                                                            AUniformRectangle<T>,
                                                                            AUniform<Utility::ValueTypeOf<T>>,
                                                                            AUniform<Utility::ValueTypeOf<T>>> {
private:
    using VOfT = Utility::ValueTypeOf<T>;
    using Base = JointParameterInterface<BasicUniformRectangleParameter<T, AUniformRectangle, AUniform>,
                                         AUniformRectangle<T>,
                                         AUniform<VOfT>,
                                         AUniform<VOfT>>;

public:
    using Base::Base;

    constexpr const auto& ParameterX() const { return this->template Parameter<0>(); }
    constexpr const auto& InfimumX() const { return ParameterX().Infimum(); }
    constexpr const auto& SupremumX() const { return ParameterX().Supremum(); }
    constexpr const auto& ParameterY() const { return this->template Parameter<1>(); }
    constexpr const auto& InfimumY() const { return ParameterY().Infimum(); }
    constexpr const auto& SupremumY() const { return ParameterY().Supremum(); }

    constexpr void ParameterX(const typename AUniform<VOfT>::ParameterType& x) { Parameter<0>(x); }
    constexpr void InfimumX(VOfT infX) { ParameterX({infX, SupremumX()}); }
    constexpr void SupremumX(VOfT supX) { ParameterX({InfimumX(), supX}); }
    constexpr void ParameterY(const typename AUniform<VOfT>::ParameterType& y) { Parameter<1>(y); }
    constexpr void InfimumY(VOfT infY) { ParameterY({infY, SupremumY()}); }
    constexpr void SupremumY(VOfT supY) { ParameterY({InfimumY(), supY}); }
};

template<template<class> class ADerived, Concept::NumericVector2Any T, template<typename> class AUniform>
class UniformRectangleBase : public JointInterface<ADerived<T>,
                                                   BasicUniformRectangleParameter<T, ADerived, AUniform>,
                                                   T,
                                                   AUniform<Utility::ValueTypeOf<T>>,
                                                   AUniform<Utility::ValueTypeOf<T>>> {
private:
    using VOfT = Utility::ValueTypeOf<T>;
    using Base = JointInterface<ADerived<T>,
                                BasicUniformRectangleParameter<T, ADerived, AUniform>,
                                T,
                                AUniform<VOfT>,
                                AUniform<VOfT>>;

public:
    using Base::Base;

protected:
    constexpr ~UniformRectangleBase() = default;

public:
    constexpr const auto& ParameterX() const { return Base::template Parameter<0>(); }
    constexpr const auto& InfimumX() const { return ParameterX().Infimum(); }
    constexpr const auto& SupremumX() const { return ParameterX().Supremum(); }
    constexpr const auto& ParameterY() const { return Base::template Parameter<1>(); }
    constexpr const auto& InfimumY() const { return ParameterY().Infimum(); }
    constexpr const auto& SupremumY() const { return ParameterY().Supremum(); }

    constexpr void ParameterX(const typename AUniform<VOfT>::ParameterType& x) { Base::template Parameter<0>(x); }
    constexpr void InfimumX(VOfT infX) { ParameterX({infX, SupremumX()}); }
    constexpr void SupremumX(VOfT supX) { ParameterX({InfimumX(), supX}); }
    constexpr void ParameterY(const typename AUniform<VOfT>::ParameterType& y) { Base::template Parameter<1>(y); }
    constexpr void InfimumY(VOfT infY) { ParameterY({infY, SupremumY()}); }
    constexpr void SupremumY(VOfT supY) { ParameterY({InfimumY(), supY}); }
};

} // namespace internal

/// @brief Generates 2D uniform random vector on a compact (including boundary) rectangular region.
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector2FloatingPoint T = std::array<double, 2>>
class UniformCompactRectangle final : public internal::UniformRectangleBase<UniformCompactRectangle, T, UniformCompact> {
public:
    using internal::UniformRectangleBase<UniformCompactRectangle, T, UniformCompact>::UniformRectangleBase;
};

template<typename T, typename U>
UniformCompactRectangle(std::initializer_list<T>, std::initializer_list<U>) -> UniformCompactRectangle<std::array<std::common_type_t<T, U>, 2>>;

template<std::floating_point T>
using UniformCompactRectangleParameter = internal::BasicUniformRectangleParameter<T, UniformCompactRectangle, UniformCompact>;

/// @brief Generates 2D uniform random vector on a open (excluding boundary) rectangular region.
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector2FloatingPoint T = std::array<double, 2>>
class UniformRealRectangle final : public internal::UniformRectangleBase<UniformRealRectangle, T, UniformReal> {
public:
    using internal::UniformRectangleBase<UniformRealRectangle, T, UniformReal>::UniformRectangleBase;
};

template<typename T, typename U>
UniformRealRectangle(std::initializer_list<T>, std::initializer_list<U>) -> UniformRealRectangle<std::array<std::common_type_t<T, U>, 2>>;

template<std::floating_point T>
using UniformRealRectangleParameter = internal::BasicUniformRectangleParameter<T, UniformRealRectangle, UniformReal>;

/// @brief Generates 2D uniform random integral vector on a rectangular region.
/// @tparam T The result vector type. It must be 2-dimensional and has integral type.
template<Concept::NumericVector2Integral T = std::array<int, 2>>
class UniformIntegerRectangle final : public internal::UniformRectangleBase<UniformIntegerRectangle, T, UniformInteger> {
public:
    using internal::UniformRectangleBase<UniformIntegerRectangle, T, UniformInteger>::UniformRectangleBase;
};

template<typename T, typename U>
UniformIntegerRectangle(std::initializer_list<T>, std::initializer_list<U>) -> UniformIntegerRectangle<std::array<std::common_type_t<T, U>, 2>>;

template<std::integral T>
using UniformIntegerRectangleParameter = internal::BasicUniformRectangleParameter<T, UniformIntegerRectangle, UniformInteger>;

} // namespace MACE::Math::Random::Distribution
