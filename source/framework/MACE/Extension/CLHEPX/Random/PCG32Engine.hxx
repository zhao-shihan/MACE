#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/PCGXSHRR6432.hxx"

namespace MACE::inline Extension::CLHEPX::Random {

class PCG32Engine final : public RandomEngineBase<Math::Random::Generator::PCGXSHRR6432> {
public:
    using RandomEngineBase<Math::Random::Generator::PCGXSHRR6432>::RandomEngineBase;

    std::string name() const override { return "PCG32Engine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
