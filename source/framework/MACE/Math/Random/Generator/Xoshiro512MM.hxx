#pragma once

#include "MACE/Math/Random/Generator/Xoshiro512Base.hxx"
#include "MACE/Utility/InlineMacro.hxx"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro512MM final : public Xoshiro512Base<Xoshiro512MM> {
public:
    constexpr Xoshiro512MM() = default;
    constexpr Xoshiro512MM(std::uint64_t seed);

    MACE_ALWAYS_INLINE constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512MM.inl"
