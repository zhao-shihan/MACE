#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"
#include "MACE/Utility/InlineMacro.hxx"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro256MM final : public Xoshiro256Base<Xoshiro256MM> {
public:
    constexpr Xoshiro256MM() = default;
    constexpr Xoshiro256MM(std::uint64_t seed);

    MACE_ALWAYS_INLINE constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256MM.inl"
