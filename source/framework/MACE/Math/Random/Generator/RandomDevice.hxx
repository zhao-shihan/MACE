#pragma once

#include "MACE/Math/Random/UniformRandomBitGeneratorBase.hxx"

#include <random>

namespace MACE::Math::Random::Generator {

class RandomDevice final : public UniformRandomBitGeneratorBase<RandomDevice, std::random_device::result_type> {
public:
    RandomDevice() = default;

    auto operator()() { return fRD(); }

    static constexpr auto Min() { return std::random_device::min(); }
    static constexpr auto Max() { return std::random_device::max(); }

private:
    std::random_device fRD;
};

} // namespace MACE::Math::Random::Generator
