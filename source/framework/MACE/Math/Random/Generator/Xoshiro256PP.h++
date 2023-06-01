#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro256PP final : public Xoshiro256Base<Xoshiro256PP> {
public:
    constexpr Xoshiro256PP() = default;
    constexpr Xoshiro256PP(std::uint64_t seed);

    MACE_ALWAYS_INLINE constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256PP.inl"
