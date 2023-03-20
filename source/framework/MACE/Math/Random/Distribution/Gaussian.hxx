#pragma once

#include "MACE/Compatibility/std2b/assume.hxx"
#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/Distribution/Gaussian2DDiagnoal.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <array>
#include <cmath>
#include <concepts>
#include <limits>

namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AGaussian>
class BasicGaussianParameter final : public DistributionParameterBase<BasicGaussianParameter<T, AGaussian>,
                                                                      AGaussian<T>> {
private:
    using Base = DistributionParameterBase<BasicGaussianParameter<T, AGaussian>,
                                           AGaussian<T>>;

public:
    constexpr BasicGaussianParameter();
    constexpr BasicGaussianParameter(T mu, T sigma);

    constexpr auto Mu() const { return fMu; }
    constexpr auto Sigma() const { return fSigma; }

    constexpr void Mu(T mu) { fMu = mu; }
    constexpr void Sigma(T sigma) { fSigma = sigma; }

    template<Concept::Character AChar, std::floating_point U, template<typename> class V>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussianParameter<U, V>& self) -> decltype(os);
    template<Concept::Character AChar, std::floating_point U, template<typename> class V>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicGaussianParameter<U, V>& self) -> decltype(is);

private:
    T fMu;
    T fSigma;
};

template<std::floating_point T, template<typename> class AGaussian>
class GaussianBase : public RandomNumberDistributionBase<AGaussian<T>,
                                                         BasicGaussianParameter<T, AGaussian>,
                                                         T> {
private:
    using Base = RandomNumberDistributionBase<AGaussian<T>,
                                              BasicGaussianParameter<T, AGaussian>,
                                              T>;

public:
    constexpr GaussianBase() = default;
    constexpr GaussianBase(T mu, T sigma);
    constexpr explicit GaussianBase(const typename Base::ParameterType& p);

protected:
    constexpr ~GaussianBase() = default;

public:
    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Mu() const { return fParameter.Mu(); }
    constexpr auto Sigma() const { return fParameter.Sigma(); }

    constexpr void Parameter(const typename Base::ParameterType& p) { fParameter = p; }
    constexpr auto Mu(T mu) const { return fParameter.Mu(mu); }
    constexpr auto Sigma(T sigma) const { return fParameter.Sigma(sigma); }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const GaussianBase& self) { return os << self.fParameter; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, GaussianBase& self) { return is >> self.fParameter; }

protected:
    typename Base::ParameterType fParameter;
};

} // namespace internal

/// @brief Reference: Luc Devroye, Non-Uniform Random Variates Generation,
/// Chapter V, Section 4.4 (See http://luc.devroye.org/rnbookindex.html).
/// @tparam T The result type.
template<std::floating_point T = double>
class Gaussian;

template<std::floating_point T>
using GaussianParameter = internal::BasicGaussianParameter<T, Gaussian>;

template<std::floating_point T>
class Gaussian final : public internal::GaussianBase<T, Gaussian> {
public:
    using internal::GaussianBase<T, Gaussian>::GaussianBase;

    constexpr void Reset() { fSaved = false; }

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const GaussianParameter<T>& p);

    constexpr auto Min() const { return std::numeric_limits<T>::lowest(); }
    constexpr auto Max() const { return std::numeric_limits<T>::max(); }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    T fSavedValue;
};

template<typename T, typename U>
Gaussian(T, U) -> Gaussian<std::common_type_t<T, U>>;

/// @brief Reference: Luc Devroye, Non-Uniform Random Variates Generation,
/// Chapter V, Section 4.4 (See http://luc.devroye.org/rnbookindex.html).
/// This version is faster than Gaussian and less accurate for a tiny bit. See
/// note.
/// @note This version uses RA2Log (P2/Q2 rational) instead of full-precision
/// Log. The average truncation error of RA2Log is O(10^-6), and the max
/// truncation error is less than 10^-5. This error will propagate to the
/// generated random numbers.
/// @tparam T The result type.
template<std::floating_point T = double>
class GaussianFast;

template<std::floating_point T>
using GaussianFastParameter = internal::BasicGaussianParameter<T, GaussianFast>;

template<std::floating_point T>
class GaussianFast final : public internal::GaussianBase<T, GaussianFast> {
public:
    using internal::GaussianBase<T, GaussianFast>::GaussianBase;

    constexpr void Reset() { fSaved = false; }

    auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    T operator()(UniformRandomBitGenerator auto& g, const GaussianFastParameter<T>& p);

    constexpr auto Min() const { return std::numeric_limits<T>::lowest(); }
    constexpr auto Max() const { return std::numeric_limits<T>::max(); }

    static constexpr auto Stateless() { return false; }

private:
    bool fSaved = false;
    T fSavedValue;
};

template<typename T, typename U>
GaussianFast(T, U) -> GaussianFast<std::common_type_t<T, U>>;

} // namespace MACE::Math::Random::inline Distribution

#include "MACE/Math/Random/Distribution/Gaussian.inl"
