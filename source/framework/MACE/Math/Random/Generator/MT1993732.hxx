#pragma once

#include "MACE/Math/Random/UniformRandomBitGeneratorBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <cstdint>
#include <limits>

namespace MACE::Math::Random::Generator {

using Utility::ObserverPtr;

class MT1993732 final : public UniformRandomBitGeneratorBase<MT1993732, std::uint32_t> {
public:
    constexpr MT1993732();
    constexpr MT1993732(ResultType seed);

    constexpr ResultType operator()();
    constexpr bool operator==(const MT1993732&) const = default;

    constexpr void Seed(ResultType seed);

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max() - 1; }

private:
    constexpr void Regenerate();

private:
    ResultType fMT[624];
    ResultType fTempered[624];
    const ObserverPtr<const ResultType> fTemperedEnd;
    ObserverPtr<const ResultType> fTemperedIterator;
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/MT1993732.inl"
