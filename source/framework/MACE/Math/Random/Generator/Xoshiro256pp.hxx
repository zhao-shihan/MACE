#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"

#include <bit>

namespace MACE::Math::Random::Generator {

class Xoshiro256pp final : public Xoshiro256Base<Xoshiro256pp> {
public:
    using Xoshiro256Base<Xoshiro256pp>::Xoshiro256Base;

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/Xoshiro256pp.inl"
