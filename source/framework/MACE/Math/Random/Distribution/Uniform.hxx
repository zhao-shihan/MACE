#pragma once

#include "MACE/Concept/InstantiatedFrom.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <concepts>
#include <istream>
#include <ostream>

namespace MACE::Math::Random::Distribution {

template<std::floating_point T>
class Uniform;

template<std::floating_point T>
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

template<std::floating_point T>
class Uniform final : public RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>> {
public:
    constexpr Uniform() = default;
    constexpr Uniform(T inf, T sup);
    constexpr Uniform(const UniformParameter<T>& p);

    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Infimum() const { return fParameter.Infimum(); }
    constexpr auto Supremum() const { return fParameter.Supremum(); }

    constexpr void Reset() { fParameter = {}; }
    constexpr void Parameter(const UniformParameter<T>& p) { fParameter = p; }
    constexpr void Infimum(T inf) { fParameter.Infimum(inf); }
    constexpr void Supremum(T sup) { fParameter.Supremum(sup); }

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p);

    constexpr auto Min() const { return Infimum(); }
    constexpr auto Max() const { return Supremum(); }

    friend auto operator<<(Concept::InstantiatedFrom<std::basic_ostream> auto& os, const Uniform& d) -> decltype(os);
    friend auto operator>>(Concept::InstantiatedFrom<std::basic_istream> auto& is, Uniform& d) -> decltype(is);

private:
    UniformParameter<T> fParameter;
};

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Uniform.inl"
