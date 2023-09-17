#pragma once

#include "MACE/Math/Random/Generator/Xoshiro512Base.h++"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro512PP final : public Xoshiro512Base<Xoshiro512PP> {
public:
    constexpr Xoshiro512PP() = default;
    constexpr explicit Xoshiro512PP(std::uint64_t seed);

    constexpr auto operator()() -> ResultType;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512PP.inl"
