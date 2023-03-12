#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/MT1993764.hxx"

namespace MACE::inline Extension::CLHEPX::Random {

class MT64Engine final : public RandomEngineBase<Math::Random::Generator::MT1993764> {
public:
    using RandomEngineBase<Math::Random::Generator::MT1993764>::RandomEngineBase;

    std::string name() const override { return "MT64Engine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
