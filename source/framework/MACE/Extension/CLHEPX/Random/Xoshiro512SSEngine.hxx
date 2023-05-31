#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/Xoshiro512SS.hxx"

namespace MACE::inline Extension::CLHEPX::Random {

class Xoshiro512SSEngine final : public RandomEngineBase<Math::Random::Xoshiro512SS> {
public:
    using RandomEngineBase<Math::Random::Xoshiro512SS>::RandomEngineBase;

    std::string name() const override { return "Xoshiro512SSEngine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
