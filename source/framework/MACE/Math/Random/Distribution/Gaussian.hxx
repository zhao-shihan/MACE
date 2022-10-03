#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <cmath>
#include <concepts>
#include <limits>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AGaussian>
class BasicGaussianParameter final : public DistributionParameterBase<BasicGaussianParameter<T, AGaussian>, AGaussian<T>> {
public:
    constexpr BasicGaussianParameter();
    constexpr BasicGaussianParameter(T mu, T sigma);

    constexpr auto Mu() const { return fMu; }
    constexpr auto Sigma() const { return fSigma; }

    constexpr void Mu(T mu) { fMu = mu; }
    constexpr void Sigma(T sigma) { fSigma = sigma; }

private:
    T fMu;
    T fSigma;
};

template<std::floating_point T, template<typename> class AGaussian>
class GaussianBase : public RandomNumberDistributionBase<AGaussian<T>, T, BasicGaussianParameter<T, AGaussian>> {
public:
    constexpr GaussianBase() = default;
    constexpr GaussianBase(T mu, T sigma);
    explicit constexpr GaussianBase(const BasicGaussianParameter<T, AGaussian>& p);

public:
    constexpr void Reset() {}

    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Mu() const { return fParameter.Mu(); }
    constexpr auto Sigma() const { return fParameter.Sigma(); }

    constexpr void Parameter(const BasicGaussianParameter<T, AGaussian>& p) { fParameter = p; }
    constexpr auto Mu(T mu) const { return fParameter.Mu(mu); }
    constexpr auto Sigma(T sigma) const { return fParameter.Sigma(sigma); }

protected:
    BasicGaussianParameter<T, AGaussian> fParameter;
};

template<Concept::Character AChar, std::floating_point T, template<typename> class AGaussian>
auto operator<<(std::basic_ostream<AChar>& os, const GaussianBase<T, AGaussian>& g) -> decltype(os);
template<Concept::Character AChar, std::floating_point T, template<typename> class AGaussian>
auto operator>>(std::basic_istream<AChar>& is, GaussianBase<T, AGaussian>& g) -> decltype(is);

} // namespace internal

template<std::floating_point T = double>
class Gaussian;

template<std::floating_point T>
using GaussianParameter = internal::BasicGaussianParameter<T, Gaussian>;

template<std::floating_point T>
class Gaussian final : public internal::GaussianBase<T, Gaussian> {
public:
    using internal::GaussianBase<T, Gaussian>::GaussianBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, const GaussianParameter<T>& p);

    // constexpr auto Min() const { return ; }
    // constexpr auto Max() const { return ; }
};

template<typename T>
Gaussian(T) -> Gaussian<T>;

template<Concept::Character AChar, std::floating_point T>
auto& operator<<(std::basic_ostream<AChar>& os, const Gaussian<T>& g) { return internal::operator<<(os, g); }
template<Concept::Character AChar, std::floating_point T>
auto& operator>>(std::basic_istream<AChar>& is, Gaussian<T>& g) { return internal::operator>>(is, g); }

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Gaussian.inl"
