#pragma once

#include "MACE/Math/Random/Generator/Xoshiro512Base.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro512SS final : public Xoshiro512Base<Xoshiro512SS> {
public:
    constexpr Xoshiro512SS() = default;
    constexpr explicit Xoshiro512SS(std::uint64_t seed);

    MACE_ALWAYS_INLINE constexpr auto operator()() -> ResultType;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512SS.inl"
