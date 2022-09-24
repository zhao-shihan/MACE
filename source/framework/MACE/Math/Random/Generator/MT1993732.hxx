#pragma once

#include "MACE/Math/Random/UniformRandomBitGeneratorBase.hxx"

#include <random>

namespace MACE::Math::Random::Generator {

class MT1993732 final : public UniformRandomBitGeneratorBase<MT1993732, std::mt19937::result_type> {
public:
    MT1993732();
    MT1993732(ResultType seed);

    auto operator()() { return fMT(); }
    void Seed(ResultType seed) { fMT.seed(seed); }

    static constexpr auto Min() { return std::mt19937::min(); }
    static constexpr auto Max() { return std::mt19937::max(); }

private:
    std::mt19937 fMT;
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/MT1993732.inl"
