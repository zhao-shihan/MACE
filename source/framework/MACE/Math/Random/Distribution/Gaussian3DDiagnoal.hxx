#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Math/Random/Distribution/Gaussian.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"

#include <array>
#include <concepts>
#include <iomanip>
#include <type_traits>
#include <utility>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector3FloatingPoint T, template<class> class AGaussian3DDiagnoal>
class BasicGaussian3DDiagnoalParameter final : public DistributionParameterBase<BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>,
                                                                                AGaussian3DDiagnoal<T>> {
private:
    using VOfT = ValueTypeOf<T>;
    using Base = DistributionParameterBase<BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>,
                                           AGaussian3DDiagnoal<T>>;

public:
    constexpr BasicGaussian3DDiagnoalParameter();
    constexpr BasicGaussian3DDiagnoalParameter(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY, std::pair<VOfT, VOfT> pZ);

    constexpr auto MuX() const { return fMuX; }
    constexpr auto SigmaX() const { return fSigmaX; }
    constexpr auto MuY() const { return fMuY; }
    constexpr auto SigmaY() const { return fSigmaY; }
    constexpr auto MuZ() const { return fMuZ; }
    constexpr auto SigmaZ() const { return fSigmaZ; }

    constexpr void MuX(VOfT muX) const { fMuX = muX; }
    constexpr void SigmaX(VOfT sigmaX) const { fSigmaX = sigmaX; }
    constexpr void MuY(VOfT muY) const { fMuY = muY; }
    constexpr void SigmaY(VOfT sigmaY) const { fSigmaY = sigmaY; }
    constexpr void MuZ(VOfT muZ) const { fMuZ = muZ; }
    constexpr void SigmaZ(VOfT sigmaZ) const { fSigmaZ = sigmaZ; }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussian3DDiagnoalParameter& self) -> decltype(os);
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicGaussian3DDiagnoalParameter& self) -> decltype(is);

private:
    VOfT fMuX;
    VOfT fSigmaX;
    VOfT fMuY;
    VOfT fSigmaY;
    VOfT fMuZ;
    VOfT fSigmaZ;
};

template<template<class> class ADerived, Concept::NumericVector3FloatingPoint T>
class Gaussian3DDiagnoalBase : public RandomNumberDistributionBase<ADerived<T>,
                                                                   BasicGaussian3DDiagnoalParameter<T, ADerived>,
                                                                   T> {
protected:
    using VOfT = ValueTypeOf<T>;

private:
    using Base = RandomNumberDistributionBase<ADerived<T>,
                                              BasicGaussian3DDiagnoalParameter<T, ADerived>,
                                              T>;

public:
    constexpr Gaussian3DDiagnoalBase() = default;
    constexpr Gaussian3DDiagnoalBase(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY, std::pair<VOfT, VOfT> pZ);
    constexpr explicit Gaussian3DDiagnoalBase(const typename Base::ParameterType& p);

protected:
    constexpr ~Gaussian3DDiagnoalBase() = default;

public:
    constexpr auto Parameter() const { return fParameter; }
    constexpr auto MuX() const { return fParameter.MuX(); }
    constexpr auto SigmaX() const { return fParameter.SigmaX(); }
    constexpr auto MuY() const { return fParameter.MuY(); }
    constexpr auto SigmaY() const { return fParameter.SigmaY(); }
    constexpr auto MuZ() const { return fParameter.MuZ(); }
    constexpr auto SigmaZ() const { return fParameter.SigmaZ(); }

    constexpr void Parameter(const typename Base::ParameterType& p) { fParameter = p; }
    constexpr void MuX(VOfT muX) const { fParameter.MuX(muX); }
    constexpr void SigmaX(VOfT sigmaX) const { fParameter.SigmaX(sigmaX); }
    constexpr void MuY(VOfT muY) const { fParameter.MuY(muY); }
    constexpr void SigmaY(VOfT sigmaY) const { fParameter.SigmaY(sigmaY); }
    constexpr void MuZ(VOfT muZ) const { fParameter.MuZ(muZ); }
    constexpr void SigmaZ(VOfT sigmaZ) const { fParameter.SigmaZ(sigmaZ); }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const Gaussian3DDiagnoalBase& self) { return os << self.fParameter; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, Gaussian3DDiagnoalBase& self) { return is >> self.fParameter; }

protected:
    typename Base::ParameterType fParameter;
};

} // namespace internal

/// @brief
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector3FloatingPoint T = stdx::array3d>
class Gaussian3DDiagnoal;

template<Concept::NumericVector3FloatingPoint T>
using Gaussian3DDiagnoalParameter = internal::BasicGaussian3DDiagnoalParameter<T, Gaussian3DDiagnoal>;

template<Concept::NumericVector3FloatingPoint T>
class Gaussian3DDiagnoal final : public internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoal, T> {
private:
    using Base = internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoal, T>;
    using VOfT = typename Base::VOfT;

public:
    using internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoal, T>::Gaussian3DDiagnoalBase;

    constexpr void Reset() { fSaved = false; }

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VOfT>::lowest(), std::numeric_limits<VOfT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VOfT>::max(), std::numeric_limits<VOfT>::max()}; }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    VOfT fSavedValue;
};

template<typename T, typename U, typename V>
Gaussian3DDiagnoal(std::initializer_list<T>, std::initializer_list<U>, std::initializer_list<V>) -> Gaussian3DDiagnoal<std::array<std::common_type_t<T, U, V>, 3>>;

/// @brief
/// @tparam T The result vector type. It must be 2-dimensional and has floating-point type.
template<Concept::NumericVector3FloatingPoint T = stdx::array3d>
class Gaussian3DDiagnoalFast;

template<Concept::NumericVector3FloatingPoint T>
using Gaussian3DDiagnoalFastParameter = internal::BasicGaussian3DDiagnoalParameter<T, Gaussian3DDiagnoalFast>;

template<Concept::NumericVector3FloatingPoint T>
class Gaussian3DDiagnoalFast final : public internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoalFast, T> {
private:
    using Base = internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoalFast, T>;
    using VOfT = typename Base::VOfT;

public:
    using internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoalFast, T>::Gaussian3DDiagnoalBase;

    constexpr void Reset() { fSaved = false; }

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalFastParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VOfT>::lowest(), std::numeric_limits<VOfT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VOfT>::max(), std::numeric_limits<VOfT>::max()}; }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    VOfT fSavedValue;
};

template<typename T, typename U, typename V>
Gaussian3DDiagnoalFast(std::initializer_list<T>, std::initializer_list<U>, std::initializer_list<V>) -> Gaussian3DDiagnoalFast<std::array<std::common_type_t<T, U, V>, 3>>;

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.inl"
