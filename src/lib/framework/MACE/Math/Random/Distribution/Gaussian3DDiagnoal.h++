#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/Random/Distribution/Gaussian.h++"
#include "MACE/Math/Random/RandomNumberDistributionBase.h++"
#include "MACE/Utility/VectorValueType.h++"

#include <array>
#include <concepts>
#include <iomanip>
#include <type_traits>
#include <utility>

namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<Concept::NumericVector3FloatingPoint T, template<typename> typename AGaussian3DDiagnoal>
class BasicGaussian3DDiagnoalParameter final : public DistributionParameterBase<BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>,
                                                                                AGaussian3DDiagnoal<T>> {
private:
    using VT = VectorValueType<T>;
    using Base = DistributionParameterBase<BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>,
                                           AGaussian3DDiagnoal<T>>;

public:
    constexpr BasicGaussian3DDiagnoalParameter();
    constexpr BasicGaussian3DDiagnoalParameter(std::pair<VT, VT> pX, std::pair<VT, VT> pY, std::pair<VT, VT> pZ);

    constexpr auto MuX() const { return fMuX; }
    constexpr auto SigmaX() const { return fSigmaX; }
    constexpr auto MuY() const { return fMuY; }
    constexpr auto SigmaY() const { return fSigmaY; }
    constexpr auto MuZ() const { return fMuZ; }
    constexpr auto SigmaZ() const { return fSigmaZ; }

    constexpr void MuX(VT muX) const { fMuX = muX; }
    constexpr void SigmaX(VT sigmaX) const { fSigmaX = sigmaX; }
    constexpr void MuY(VT muY) const { fMuY = muY; }
    constexpr void SigmaY(VT sigmaY) const { fSigmaY = sigmaY; }
    constexpr void MuZ(VT muZ) const { fMuZ = muZ; }
    constexpr void SigmaZ(VT sigmaZ) const { fSigmaZ = sigmaZ; }

    template<Concept::Character AChar, Concept::NumericVector3FloatingPoint U, template<typename> typename V>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussian3DDiagnoalParameter<U, V>& self) -> decltype(os);
    template<Concept::Character AChar, Concept::NumericVector3FloatingPoint U, template<typename> typename V>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicGaussian3DDiagnoalParameter<U, V>& self) -> decltype(is);

private:
    VT fMuX;
    VT fSigmaX;
    VT fMuY;
    VT fSigmaY;
    VT fMuZ;
    VT fSigmaZ;
};

template<template<typename> typename ADerived, Concept::NumericVector3FloatingPoint T>
class Gaussian3DDiagnoalBase : public RandomNumberDistributionBase<ADerived<T>,
                                                                   BasicGaussian3DDiagnoalParameter<T, ADerived>,
                                                                   T> {
protected:
    using VT = VectorValueType<T>;

private:
    using Base = RandomNumberDistributionBase<ADerived<T>,
                                              BasicGaussian3DDiagnoalParameter<T, ADerived>,
                                              T>;

public:
    constexpr Gaussian3DDiagnoalBase() = default;
    constexpr Gaussian3DDiagnoalBase(std::pair<VT, VT> pX, std::pair<VT, VT> pY, std::pair<VT, VT> pZ);
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
    constexpr void MuX(VT muX) const { fParameter.MuX(muX); }
    constexpr void SigmaX(VT sigmaX) const { fParameter.SigmaX(sigmaX); }
    constexpr void MuY(VT muY) const { fParameter.MuY(muY); }
    constexpr void SigmaY(VT sigmaY) const { fParameter.SigmaY(sigmaY); }
    constexpr void MuZ(VT muZ) const { fParameter.MuZ(muZ); }
    constexpr void SigmaZ(VT sigmaZ) const { fParameter.SigmaZ(sigmaZ); }

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
    using VT = typename Base::VT;

public:
    using internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoal, T>::Gaussian3DDiagnoalBase;

    constexpr void Reset() { fSaved = false; }

    MACE_STRONG_INLINE auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_STRONG_INLINE T operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VT>::lowest(), std::numeric_limits<VT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VT>::max(), std::numeric_limits<VT>::max()}; }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    VT fSavedValue;
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
    using VT = typename Base::VT;

public:
    using internal::Gaussian3DDiagnoalBase<Gaussian3DDiagnoalFast, T>::Gaussian3DDiagnoalBase;

    constexpr void Reset() { fSaved = false; }

    MACE_STRONG_INLINE auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_STRONG_INLINE T operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalFastParameter<T>& p);

    constexpr T Min() const { return {std::numeric_limits<VT>::lowest(), std::numeric_limits<VT>::lowest()}; }
    constexpr T Max() const { return {std::numeric_limits<VT>::max(), std::numeric_limits<VT>::max()}; }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    VT fSavedValue;
};

template<typename T, typename U, typename V>
Gaussian3DDiagnoalFast(std::initializer_list<T>, std::initializer_list<U>, std::initializer_list<V>) -> Gaussian3DDiagnoalFast<std::array<std::common_type_t<T, U, V>, 3>>;

} // namespace MACE::Math::Random::inline Distribution

#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.inl"
