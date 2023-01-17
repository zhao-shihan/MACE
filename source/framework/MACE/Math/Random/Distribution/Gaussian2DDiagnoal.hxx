#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Math/Hypot.hxx"
#include "MACE/Math/Log.hxx"
#include "MACE/Math/RALog.hxx"
#include "MACE/Math/Random/Distribution/UniformRectangle.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"

#include <array>
#include <concepts>
#include <iomanip>
#include <type_traits>
#include <utility>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector2FloatingPoint T, template<class> class AGaussian2DDiagnoal>
class BasicGaussian2DDiagnoalParameter final : public DistributionParameterBase<BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>,
                                                                                AGaussian2DDiagnoal<T>> {
private:
    using VOfT = Utility::ValueTypeOf<T>;
    using Base = DistributionParameterBase<BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>,
                                           AGaussian2DDiagnoal<T>>;

public:
    constexpr BasicGaussian2DDiagnoalParameter();
    constexpr BasicGaussian2DDiagnoalParameter(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY);

    constexpr auto MuX() const { return fMuX; }
    constexpr auto SigmaX() const { return fSigmaX; }
    constexpr auto MuY() const { return fMuY; }
    constexpr auto SigmaY() const { return fSigmaY; }

    constexpr void MuX(VOfT muX) const { fMuX = muX; }
    constexpr void SigmaX(VOfT sigmaX) const { fSigmaX = sigmaX; }
    constexpr void MuY(VOfT muY) const { fMuY = muY; }
    constexpr void SigmaY(VOfT sigmaY) const { fSigmaY = sigmaY; }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussian2DDiagnoalParameter& self) -> decltype(os);
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicGaussian2DDiagnoalParameter& self) -> decltype(is);

private:
    VOfT fMuX;
    VOfT fSigmaX;
    VOfT fMuY;
    VOfT fSigmaY;
};

template<template<class> class ADerived, Concept::NumericVector2FloatingPoint T>
class Gaussian2DDiagnoalBase : public RandomNumberDistributionBase<ADerived<T>,
                                                                   BasicGaussian2DDiagnoalParameter<T, ADerived>,
                                                                   T> {
protected:
    using VOfT = Utility::ValueTypeOf<T>;

private:
    using Base = RandomNumberDistributionBase<ADerived<T>,
                                              BasicGaussian2DDiagnoalParameter<T, ADerived>,
                                              T>;

public:
    constexpr Gaussian2DDiagnoalBase() = default;
    constexpr Gaussian2DDiagnoalBase(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY);
    constexpr explicit Gaussian2DDiagnoalBase(const typename Base::ParameterType& p);

protected:
    constexpr ~Gaussian2DDiagnoalBase() = default;

public:
    constexpr auto Parameter() const { return fParameter; }
    constexpr auto MuX() const { return fParameter.MuX(); }
    constexpr auto SigmaX() const { return fParameter.SigmaX(); }
    constexpr auto MuY() const { return fParameter.MuY(); }
    constexpr auto SigmaY() const { return fParameter.SigmaY(); }

    constexpr void Parameter(const typename Base::ParameterType& p) { fParameter = p; }
    constexpr void MuX(VOfT muX) const { fParameter.MuX(muX); }
    constexpr void SigmaX(VOfT sigmaX) const { fParameter.SigmaX(sigmaX); }
    constexpr void MuY(VOfT muY) const { fParameter.MuY(muY); }
    constexpr void SigmaY(VOfT sigmaY) const { fParameter.SigmaY(sigmaY); }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const Gaussian2DDiagnoalBase& self) { return os << self.fParameter; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, Gaussian2DDiagnoalBase& self) { return is >> self.fParameter; }

protected:
    typename Base::ParameterType fParameter;
};

} // namespace internal

/// @brief
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector2FloatingPoint T = std::array<double, 2>>
class Gaussian2DDiagnoal;

template<Concept::NumericVector2FloatingPoint T>
using Gaussian2DDiagnoalParameter = internal::BasicGaussian2DDiagnoalParameter<T, Gaussian2DDiagnoal>;

template<Concept::NumericVector2FloatingPoint T>
class Gaussian2DDiagnoal final : public internal::Gaussian2DDiagnoalBase<Gaussian2DDiagnoal, T> {
private:
    using Base = internal::Gaussian2DDiagnoalBase<Gaussian2DDiagnoal, T>;
    using VOfT = Base::VOfT;

public:
    using Base::Gaussian2DDiagnoalBase;

    constexpr void Reset() {}

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VOfT>::lowest(), std::numeric_limits<VOfT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VOfT>::max(), std::numeric_limits<VOfT>::max()}; }

    static constexpr auto Stateless() { return true; }
};

template<typename T, typename U>
Gaussian2DDiagnoal(std::initializer_list<T>, std::initializer_list<U>) -> Gaussian2DDiagnoal<std::array<std::common_type_t<T, U>, 2>>;

/// @brief
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector2FloatingPoint T = std::array<double, 2>>
class Gaussian2DDiagnoalFast;

template<Concept::NumericVector2FloatingPoint T>
using Gaussian2DDiagnoalFastParameter = internal::BasicGaussian2DDiagnoalParameter<T, Gaussian2DDiagnoalFast>;

template<Concept::NumericVector2FloatingPoint T>
class Gaussian2DDiagnoalFast final : public internal::Gaussian2DDiagnoalBase<Gaussian2DDiagnoalFast, T> {
private:
    using Base = internal::Gaussian2DDiagnoalBase<Gaussian2DDiagnoalFast, T>;
    using VOfT = Base::VOfT;

public:
    using Base::Gaussian2DDiagnoalBase;

    constexpr void Reset() {}

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalFastParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VOfT>::lowest(), std::numeric_limits<VOfT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VOfT>::max(), std::numeric_limits<VOfT>::max()}; }

    static constexpr auto Stateless() { return true; }
};

template<typename T, typename U>
Gaussian2DDiagnoalFast(std::initializer_list<T>, std::initializer_list<U>) -> Gaussian2DDiagnoalFast<std::array<std::common_type_t<T, U>, 2>>;

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Gaussian2DDiagnoal.inl"
