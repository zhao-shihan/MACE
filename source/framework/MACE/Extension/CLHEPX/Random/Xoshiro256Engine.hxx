#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.hxx"

namespace MACE::inline Extension::CLHEPX::Random {

class Xoshiro256Engine final : public RandomEngineBase<Math::Random::Generator::Xoshiro256Plus> {
public:
    using RandomEngineBase<Math::Random::Generator::Xoshiro256Plus>::RandomEngineBase;

    std::string name() const override { return "Xoshiro256Engine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
