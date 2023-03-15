#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"

namespace MACE::Math::Random::Generator {

class Xoshiro256Plus final : public Xoshiro256Base<Xoshiro256Plus> {
public:
    using Xoshiro256Base<Xoshiro256Plus>::Xoshiro256Base;

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/Xoshiro256Plus.inl"
