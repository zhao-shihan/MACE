#pragma once

#include "MACE/Extension/ROOTX/Math/WrapAsTRandom.h++"
#include "MACE/Math/Random/Generator/Xoshiro256PP.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Math/Random/Generator/Xoshiro256SS.h++"
#include "MACE/Math/Random/Generator/Xoshiro512PP.h++"
#include "MACE/Math/Random/Generator/Xoshiro512Plus.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"

namespace MACE::inline Extension::ROOTX::Math {

using Xoshiro256SS = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro256SS>;
using Xoshiro256PP = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro256PP>;
using Xoshiro256Plus = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro256Plus>;
using Xoshiro512SS = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro512SS>;
using Xoshiro512PP = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro512PP>;
using Xoshiro512Plus = ROOTX::Math::WrapAsTRandom<MACE::Math::Random::Xoshiro512Plus>;

} // namespace MACE::inline Extension::ROOTX::Math
