#pragma once

#include "MACE/Extension/CLHEPX/Random/Wrap.h++"
#include "MACE/Math/Random/Generator/MT1993732.h++"
#include "MACE/Math/Random/Generator/MT1993764.h++"

namespace MACE::inline Extension::CLHEPX::Random {

using MT1993732 = CLHEPX::Random::Wrap<Math::Random::MT1993732>;
using MT1993764 = CLHEPX::Random::Wrap<Math::Random::MT1993764>;

} // namespace MACE::inline Extension::CLHEPX::Random
