#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <concepts>
#include <iomanip>
#include <random>
#include <type_traits>

namespace MACE::Math::Random::Distribution {

template<std::floating_point T = double>
class UniformReal;

template<std::integral T = int>
class UniformInteger;

template<Concept::Arithmetic T>
using Uniform = std::conditional_t<std::floating_point<T>,
                                   UniformReal<std::conditional_t<std::floating_point<T>, T, double>>,
                                   UniformInteger<std::conditional_t<std::integral<T>, T, int>>>;

template<Concept::Arithmetic T>
class UniformParameter final : public DistributionParameterBase<UniformParameter<T>, Uniform<T>> {
public:
    constexpr UniformParameter();
    constexpr UniformParameter(T inf, T sup);

    constexpr auto Infimum() const { return fInfimum; }
    constexpr auto Supremum() const { return fSupremum; }

    constexpr void Infimum(T inf) { fInfimum = inf; }
    constexpr void Supremum(T sup) { fSupremum = sup; }

private:
    T fInfimum;
    T fSupremum;
};

namespace internal {

template<Concept::Arithmetic T>
class UniformBase : public RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>> {
public:
    constexpr UniformBase() = default;
    constexpr UniformBase(T inf, T sup);
    constexpr UniformBase(const UniformParameter<T>& p);

protected:
    constexpr ~UniformBase() = default;

public:
    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Infimum() const { return fParameter.Infimum(); }
    constexpr auto Supremum() const { return fParameter.Supremum(); }

    constexpr void Reset() { fParameter = {}; }
    constexpr void Parameter(const UniformParameter<T>& p) { fParameter = p; }
    constexpr void Infimum(T inf) { fParameter.Infimum(inf); }
    constexpr void Supremum(T sup) { fParameter.Supremum(sup); }

    constexpr auto Min() const { return Infimum(); }
    constexpr auto Max() const { return Supremum(); }

protected:
    UniformParameter<T> fParameter;
};

template<Concept::Character AChar, Concept::Arithmetic T>
auto operator<<(std::basic_ostream<AChar>& os, const UniformBase<T>& u) -> decltype(os);
template<Concept::Character AChar, Concept::Arithmetic T>
auto operator>>(std::basic_istream<AChar>& is, UniformBase<T>& u) -> decltype(is);

} // namespace internal

template<std::floating_point T>
class UniformReal final : public internal::UniformBase<T> {
public:
    using internal::UniformBase<T>::UniformBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p);
};

template<std::integral T>
class UniformInteger final : public internal::UniformBase<T> {
public:
    using internal::UniformBase<T>::UniformBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p);
};

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Uniform.inl"
