#pragma once

#include "MACE/CLHEPX/Random/RandomEngineBase.hxx"
#include "MACE/Math/Random/Generator/PCGXSHRR6432.hxx"

namespace MACE::CLHEPX::Random {

class PCG32Engine final : public RandomEngineBase<Math::Random::Generator::PCGXSHRR6432> {
public:
    using RandomEngineBase<Math::Random::Generator::PCGXSHRR6432>::RandomEngineBase;

    std::string name() const override { return "PCG32Engine"; }
};

} // namespace MACE::CLHEPX::Random
