#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.h++"
#include "MACE/Math/Random/Generator/MT1993764.h++"

namespace MACE::inline Extension::CLHEPX::Random {

class MT1993764Engine final : public RandomEngineBase<Math::Random::MT1993764> {
public:
    using RandomEngineBase<Math::Random::MT1993764>::RandomEngineBase;

    std::string name() const override { return "MT1993764Engine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
