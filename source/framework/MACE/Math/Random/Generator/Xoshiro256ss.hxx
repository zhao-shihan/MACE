#pragma once

#include "MACE/Math/Random/Generator/Xoshiro256Base.hxx"

#include <bit>

namespace MACE::Math::Random::Generator {

class Xoshiro256ss final : public Xoshiro256Base<Xoshiro256ss> {
public:
    using Xoshiro256Base<Xoshiro256ss>::Xoshiro256Base;

    constexpr ResultType operator()();
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/Xoshiro256ss.inl"
