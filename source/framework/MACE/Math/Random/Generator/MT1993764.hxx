#pragma once

#include "MACE/Math/Random/UniformRandomBitGeneratorBase.hxx"

#include <random>

namespace MACE::Math::Random::Generator {

class MT1993764 final : public UniformRandomBitGeneratorBase<MT1993764, std::mt19937_64::result_type> {
public:
    MT1993764();
    MT1993764(ResultType seed);

    auto operator()() { return fMT(); }
    void Seed(ResultType seed) { fMT.seed(seed); }

    static constexpr auto Min() { return std::mt19937_64::min(); }
    static constexpr auto Max() { return std::mt19937_64::max(); }

private:
    std::mt19937_64 fMT;
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/MT1993764.inl"
