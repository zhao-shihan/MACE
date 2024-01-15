#pragma once

#include "MACE/Math/Random/UniformPseudoRandomBitGenerator.h++"
#include "MACE/Math/Random/UniformRandomBitGeneratorBase.h++"

#include <concepts>
#include <utility>

namespace MACE::Math::Random {

/// @brief Well-formed derivation of this class fulfills
/// the concept UniformPseudoRandomBitGenerator.
/// @tparam ADerived The finally derived class.
/// @tparam AResult The output type of derived PRBG.
template<typename ADerived,
         std::unsigned_integral AResult,
         std::unsigned_integral ASeed>
class UniformPseudoRandomBitGeneratorBase : public UniformRandomBitGeneratorBase<ADerived, AResult> {
public:
    using SeedType = ASeed;

protected:
    constexpr UniformPseudoRandomBitGeneratorBase();
    constexpr ~UniformPseudoRandomBitGeneratorBase() = default;

public:
    auto seed(SeedType s) -> void { return static_cast<ADerived*>(this)->Seed(s); }
};

} // namespace MACE::Math::Random

#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.inl"
