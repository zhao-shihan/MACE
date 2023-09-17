#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.h++"
#include "MACE/Math/Random/Generator/Xoshiro256SS.h++"

namespace MACE::inline Extension::CLHEPX::Random {

class Xoshiro256SSEngine final : public RandomEngineBase<Math::Random::Xoshiro256SS> {
public:
    using RandomEngineBase<Math::Random::Xoshiro256SS>::RandomEngineBase;

    auto name() const -> std::string override { return "Xoshiro256SSEngine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
