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
template<class ADerived, std::unsigned_integral AResult>
class UniformPseudoRandomBitGeneratorBase : public UniformRandomBitGeneratorBase<ADerived, AResult> {
protected:
    constexpr UniformPseudoRandomBitGeneratorBase();
    constexpr ~UniformPseudoRandomBitGeneratorBase() = default;

public:
    decltype(auto) seed(auto&& s) { return static_cast<ADerived*>(this)->Seed(std::forward<decltype(s)>(s)); }
};

} // namespace MACE::Math::Random

#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.inl"
