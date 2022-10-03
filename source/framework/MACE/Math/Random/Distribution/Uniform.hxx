#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include <concepts>
#include <iomanip>
#include <random>
#include <type_traits>

namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::Arithmetic T, template<typename> class AUniform>
class BasicUniformParameter final : public DistributionParameterBase<BasicUniformParameter<T, AUniform>, AUniform<T>> {
public:
    constexpr BasicUniformParameter();
    constexpr BasicUniformParameter(T inf, T sup);

    constexpr auto Infimum() const { return fInfimum; }
    constexpr auto Supremum() const { return fSupremum; }

    constexpr void Infimum(T inf) { fInfimum = inf; }
    constexpr void Supremum(T sup) { fSupremum = sup; }

private:
    T fInfimum;
    T fSupremum;
};

template<Concept::Arithmetic T, template<typename> class AUniform>
class UniformBase : public RandomNumberDistributionBase<AUniform<T>, T, BasicUniformParameter<T, AUniform>> {
public:
    constexpr UniformBase() = default;
    constexpr UniformBase(T inf, T sup);
    explicit constexpr UniformBase(BasicUniformParameter<T, AUniform> p);

protected:
    constexpr ~UniformBase() = default;

public:
    constexpr void Reset() {}

    constexpr auto Parameter() const { return fParameter; }
    constexpr auto Infimum() const { return fParameter.Infimum(); }
    constexpr auto Supremum() const { return fParameter.Supremum(); }

    constexpr void Parameter(BasicUniformParameter<T, AUniform> p) { fParameter = p; }
    constexpr void Infimum(T inf) { fParameter.Infimum(inf); }
    constexpr void Supremum(T sup) { fParameter.Supremum(sup); }

    constexpr auto Min() const { return Infimum(); }
    constexpr auto Max() const { return Supremum(); }

protected:
    BasicUniformParameter<T, AUniform> fParameter;
};

template<Concept::Character AChar, Concept::Arithmetic T, template<typename> class AUniform>
auto operator<<(std::basic_ostream<AChar>& os, const UniformBase<T, AUniform>& u) -> decltype(os);
template<Concept::Character AChar, Concept::Arithmetic T, template<typename> class AUniform>
auto operator>>(std::basic_istream<AChar>& is, UniformBase<T, AUniform>& u) -> decltype(is);

} // namespace internal

template<std::floating_point T = double>
class CompactUniform;

template<std::floating_point T>
using CompactUniformParameter = internal::BasicUniformParameter<T, CompactUniform>;

template<std::floating_point T>
class CompactUniform final : public internal::UniformBase<T, CompactUniform> {
public:
    using internal::UniformBase<T, CompactUniform>::UniformBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, CompactUniformParameter<T> p);
};

template<typename T, typename U>
CompactUniform(T, U) -> CompactUniform<std::common_type_t<T, U>>;

template<std::floating_point T = double>
class UniformReal;

template<std::integral T = int>
class UniformInteger;

template<Concept::Arithmetic T>
using Uniform = std::conditional_t<std::floating_point<T>,
                                   UniformReal<std::conditional_t<std::floating_point<T>, T, double>>,
                                   UniformInteger<std::conditional_t<std::integral<T>, T, int>>>;

template<Concept::Arithmetic T>
using UniformParameter = internal::BasicUniformParameter<T, Uniform>;

template<std::floating_point T>
class UniformReal final : public internal::UniformBase<T, Uniform> {
public:
    using internal::UniformBase<T, Uniform>::UniformBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, UniformParameter<T> p);
};

template<typename T, typename U>
UniformReal(T, U) -> UniformReal<std::common_type_t<T, U>>;

template<std::integral T>
class UniformInteger final : public internal::UniformBase<T, Uniform> {
public:
    using internal::UniformBase<T, Uniform>::UniformBase;

    constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    constexpr T operator()(UniformRandomBitGenerator auto& g, UniformParameter<T> p);
};

template<typename T, typename U>
UniformInteger(T, U) -> UniformInteger<std::common_type_t<T, U>>;

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Uniform.inl"
