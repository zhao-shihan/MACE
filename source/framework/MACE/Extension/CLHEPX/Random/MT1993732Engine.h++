#pragma once

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.h++"
#include "MACE/Math/Random/Generator/MT1993732.h++"

namespace MACE::inline Extension::CLHEPX::Random {

class MT1993732Engine final : public RandomEngineBase<Math::Random::MT1993732> {
public:
    using RandomEngineBase<Math::Random::MT1993732>::RandomEngineBase;

    auto name() const -> std::string override { return "MT1993732Engine"; }
};

} // namespace MACE::inline Extension::CLHEPX::Random
