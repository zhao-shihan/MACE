#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/RandomNumberDistribution.hxx"

namespace MACE::Math::Random {

template<class ADerived, class ADistribution>
class DistributionParameterBase {
public:
    using DistributionType = ADistribution;
    using distribution_type = DistributionType;

protected:
    constexpr DistributionParameterBase();
    constexpr ~DistributionParameterBase() = default;

public:
    constexpr bool operator==(const DistributionParameterBase&) const = default;
};

template<class ADerived, Concept::Arithmetic AResult, class AParameter>
class RandomNumberDistributionBase {
public:
    using ResultType = AResult;
    using ParameterType = AParameter;
    using result_type = ResultType;
    using param_type = ParameterType;

protected:
    constexpr RandomNumberDistributionBase();
    constexpr ~RandomNumberDistributionBase() = default;

public:
    void reset() { static_cast<ADerived*>(this)->Reset(); }
    auto param() const { return static_cast<const ADerived*>(this)->Parameter(); }
    void param(const AParameter& p) { static_cast<ADerived*>(this)->Parameter(p); }
    auto min() const { return static_cast<const ADerived*>(this)->Min(); }
    auto max() const { return static_cast<const ADerived*>(this)->Max(); }

    constexpr bool operator==(const RandomNumberDistributionBase&) const = default;
};

} // namespace MACE::Math::Random

#include "MACE/Math/Random/RandomNumberDistributionBase.inl"
