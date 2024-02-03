#pragma once

#include "MACE/Math/Random/Generator/Xoshiro512Base.h++"
#include "MACE/Utility/InlineMacro.h++"

namespace MACE::Math::Random::inline Generator {

class Xoshiro512Plus final : public Xoshiro512Base<Xoshiro512Plus> {
public:
    constexpr Xoshiro512Plus() = default;
    constexpr explicit Xoshiro512Plus(SeedType seed);

    MACE_ALWAYS_INLINE constexpr auto operator()() -> ResultType;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512Plus.inl"
