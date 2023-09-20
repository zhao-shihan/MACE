#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro256SS final : public Xoshiro256Base<Xoshiro256SS> {
public:
    constexpr Xoshiro256SS() = default;
    constexpr explicit Xoshiro256SS(SeedType seed);

    MACE_ALWAYS_INLINE constexpr auto operator()() -> ResultType;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256SS.inl"
