#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.hxx"

#include <random>

namespace MACE::Math::Random::inline Generator {

class MT1993732 final : public UniformPseudoRandomBitGeneratorBase<MT1993732, std::mt19937::result_type> {
public:
    MT1993732() = default;
    MT1993732(ResultType seed);

    auto operator()() { return fMT(); }
    void Seed(ResultType seed) { fMT.seed(seed); }

    static constexpr auto Min() { return std::mt19937::min(); }
    static constexpr auto Max() { return std::mt19937::max(); }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const MT1993732& self) { return os << self.fMT; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, MT1993732& self) { return is >> self.fMT; }

private:
    std::mt19937 fMT;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/MT1993732.inl"
