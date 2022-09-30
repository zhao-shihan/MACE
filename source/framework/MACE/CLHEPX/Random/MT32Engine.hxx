#pragma once

#include "MACE/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/MT1993732.hxx"

namespace MACE::CLHEPX::Random {

class MT32Engine final : public RandomEngineBase<Math::Random::Generator::MT1993732> {
public:
    using RandomEngineBase<Math::Random::Generator::MT1993732>::RandomEngineBase;

    std::string name() const override { return "MT32Engine"; }
};

} // namespace MACE::CLHEPX::Random
