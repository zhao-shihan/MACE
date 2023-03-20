#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"

#include <bit>

namespace MACE::Math::Random::inline Generator {

class Xoshiro256PP final : public Xoshiro256Base<Xoshiro256PP> {
public:
    using Xoshiro256Base<Xoshiro256PP>::Xoshiro256Base;

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256PP.inl"
