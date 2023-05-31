#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/Xoshiro256SS.hxx"

namespace MACE::inline Extension::CLHEPX::Random {

class Xoshiro256SSEngine final : public RandomEngineBase<Math::Random::Xoshiro256SS> {
public:
    using RandomEngineBase<Math::Random::Xoshiro256SS>::RandomEngineBase;

    std::string name() const override { return "Xoshiro256SSEngine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
