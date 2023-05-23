#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Log.hxx"
#include "MACE/Math/Random/Distribution/internal/FastLogForCompact01.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/InlineMacro.hxx"

#include <concepts>
#include <iomanip>
#include <limits>

namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AExponential>
class BasicExponentialParameter final : public DistributionParameterBase<BasicExponentialParameter<T, AExponential>,
                                                                         AExponential<T>> {
private:
    using Base = DistributionParameterBase<BasicExponentialParameter<T, AExponential>,
                                           AExponential<T>>;

public:
    constexpr BasicExponentialParameter();
    constexpr BasicExponentialParameter(T expectation);

    constexpr auto Expectation() const { return fExpectation; }

    constexpr void Expectation(T expectation) { fExpectation = expectation; }

    template<Concept::Character AChar, std::floating_point U, template<typename> class V>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicExponentialParameter<U, V>& self) -> decltype(os);
    template<Concept::Character AChar, std::floating_point U, template<typename> class V>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicExponentialParameter<U, V>& self) -> decltype(is);

private:
    T fExpectation;
};

template<template<typename> class ADerived, std::floating_point T>
class ExponentialBase : public RandomNumberDistributionBase<ADerived<T>,
                                                            BasicExponentialParameter<T, ADerived>,
                                                            T> {
private:
    using Base = RandomNumberDistributionBase<ADerived<T>,
                                              BasicExponentialParameter<T, ADerived>,
                                              T>;

public:
    constexpr ExponentialBase() = default;
    constexpr explicit ExponentialBase(T expectation);
    constexpr explicit ExponentialBase(const typename Base::ParameterType& p);

protected:
    constexpr ~ExponentialBase() = default;

public:
    constexpr void Reset() {}

    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Expectation() const { return fParameter.Expectation(); }

    constexpr void Parameter(const typename Base::ParameterType& p) { fParameter = p; }
    constexpr void Expectation(T expectation) { fParameter.Expectation(expectation); }

    constexpr auto Min() const { return std::numeric_limits<T>::min(); }
    constexpr auto Max() const { return std::numeric_limits<T>::max(); }

    static constexpr auto Stateless() { return true; }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const ExponentialBase& self) { return os << self.fParameter; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, ExponentialBase& self) { return is >> self.fParameter; }

protected:
    typename Base::ParameterType fParameter;
};

} // namespace internal

/// @brief Generates random floating-points of exponential distribution.
/// @tparam T The type of the result.
template<std::floating_point T = double>
class Exponential;

template<std::floating_point T>
using ExponentialParameter = internal::BasicExponentialParameter<T, Exponential>;

template<std::floating_point T>
class Exponential final : public internal::ExponentialBase<Exponential, T> {
public:
    using internal::ExponentialBase<Exponential, T>::ExponentialBase;

    MACE_STRONG_INLINE constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_STRONG_INLINE constexpr T operator()(UniformRandomBitGenerator auto& g, const ExponentialParameter<T>& p);
};

template<typename T>
Exponential(T) -> Exponential<T>;

/// @brief Generates random floating-points of exponential distribution. This
/// version is faster than Exponential and less accurate for a tiny bit. See
/// note.
/// @note This version uses RA2Log (P2/Q2 rational) instead of full-precision
/// Log. The average truncation error of RA2Log is O(10^-6), and the max
/// truncation error is less than 10^-5. This error will propagate to the
/// generated random numbers.
/// @tparam T The type of the result.
template<std::floating_point T = double>
class ExponentialFast;

template<std::floating_point T>
using ExponentialFastParameter = internal::BasicExponentialParameter<T, ExponentialFast>;

template<std::floating_point T>
class ExponentialFast final : public internal::ExponentialBase<ExponentialFast, T> {
public:
    using internal::ExponentialBase<ExponentialFast, T>::ExponentialBase;

    MACE_ALWAYS_INLINE constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_ALWAYS_INLINE constexpr T operator()(UniformRandomBitGenerator auto& g, const ExponentialFastParameter<T>& p);
};

template<typename T>
ExponentialFast(T) -> ExponentialFast<T>;

} // namespace MACE::Math::Random::inline Distribution

#include "MACE/Math/Random/Distribution/Exponential.inl"
