#pragma once

#include "MACE/Math/Random/Generator/Xoshiro512Base.h++"

namespace MACE::Math::Random::inline Generator {

class Xoshiro512Plus final : public Xoshiro512Base<Xoshiro512Plus> {
public:
    constexpr Xoshiro512Plus() = default;
    constexpr Xoshiro512Plus(std::uint64_t seed);

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512Plus.inl"
