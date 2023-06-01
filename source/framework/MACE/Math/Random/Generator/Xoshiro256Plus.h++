#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.h++"
#include "MACE/Utility/InlineMacro.h++"

namespace MACE::Math::Random::inline Generator {

class Xoshiro256Plus final : public Xoshiro256Base<Xoshiro256Plus> {
public:
    constexpr Xoshiro256Plus() = default;
    constexpr Xoshiro256Plus(std::uint64_t seed);

    MACE_ALWAYS_INLINE constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256Plus.inl"
