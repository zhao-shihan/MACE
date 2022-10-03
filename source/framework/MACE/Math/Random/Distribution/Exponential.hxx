#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <cmath>
#include <concepts>
#include <limits>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AExponential>
class BasicExponentialParameter final : public DistributionParameterBase<BasicExponentialParameter<T, AExponential>, AExponential<T>> {
public:
    constexpr BasicExponentialParameter();
    constexpr BasicExponentialParameter(T expectation);

    constexpr auto Expectation() const { return fExpectation; }

    constexpr void Expectation(T expectation) { fExpectation = expectation; }

private:
    T fExpectation;
};

template<std::floating_point T, template<typename> class AExponential>
class ExponentialBase : public RandomNumberDistributionBase<AExponential<T>, T, BasicExponentialParameter<T, AExponential>> {
public:
    constexpr ExponentialBase() = default;
    explicit constexpr ExponentialBase(T expectation);
    explicit constexpr ExponentialBase(BasicExponentialParameter<T, AExponential> p);

protected:
    constexpr ~ExponentialBase() = default;

public:
    constexpr void Reset() {}

    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Expectation() const { return fParameter.Expectation(); }

    constexpr void Parameter(BasicExponentialParameter<T, AExponential> p) { fParameter = p; }
    constexpr void Expectation(T expectation) { fParameter.Expectation(expectation); }

    constexpr auto Min() const { return static_cast<T>(0); }
    constexpr auto Max() const { return std::numeric_limits<T>::infinity(); }

protected:
    BasicExponentialParameter<T, AExponential> fParameter;
};

template<Concept::Character AChar, std::floating_point T, template<typename> class AExponential>
auto operator<<(std::basic_ostream<AChar>& os, const ExponentialBase<T, AExponential>& e) -> decltype(os);
template<Concept::Character AChar, std::floating_point T, template<typename> class AExponential>
auto operator>>(std::basic_istream<AChar>& is, ExponentialBase<T, AExponential>& e) -> decltype(is);

} // namespace internal

template<std::floating_point T = double>
class Exponential;

template<std::floating_point T>
using ExponentialParameter = internal::BasicExponentialParameter<T, Exponential>;

template<std::floating_point T>
class Exponential final : public internal::ExponentialBase<T, Exponential> {
public:
    using internal::ExponentialBase<T, Exponential>::ExponentialBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, ExponentialParameter<T> p);
};

template<typename T>
Exponential(T) -> Exponential<T>;

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Exponential.inl"
