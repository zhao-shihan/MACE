#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"

#include <bit>

namespace MACE::Math::Random::Generator {

class Xoshiro256MM final : public Xoshiro256Base<Xoshiro256MM> {
public:
    using Xoshiro256Base<Xoshiro256MM>::Xoshiro256Base;

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/Xoshiro256MM.inl"
