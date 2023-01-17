#pragma once

#include "MACE/Concept/StreamIOable.hxx"
#include "MACE/Math/Random/UniformRandomBitGenerator.hxx"

#include <concepts>
#include <random>
#include <type_traits>

namespace MACE::Math::Random {

template<class ADerived, std::unsigned_integral AResult>
class UniformPseudoRandomBitGeneratorBase;

/// @brief Concept of uniform pseudo random bit generator.
template<class G>
concept UniformPseudoRandomBitGenerator =
    requires(G& g) {
        // 1. A UniformPseudoRandomBitGenerator satisfies UniformRandomBitGenerator.
        requires UniformRandomBitGenerator<G>;
        // 2. It is constructible from a seed.
        requires std::constructible_from<G, const typename G::ResultType>;
        // 3. It is seedable.
        requires requires(const typename G::ResultType seed) {
                     { g.Seed(seed) } -> std::same_as<void>;
                 };
        // 4. It is equality comparable. Given two UniformPseudoRandomBitGenerator
        // g1, g2, g1 == g2 is true means the following calls to g1() and g2()
        // produce exactly the same number sequence.
        requires std::equality_comparable<G>;
        // 5. It is copyable. Given a UniformPseudoRandomBitGenerator g, G(g) == g
        // always hold.
        requires std::copyable<G>;
        // 6. It is TriviallyCopyable (a C++ named requirements).
        requires std::is_trivially_copyable_v<G>;
        // 7. It is a standard-layout type.
        requires std::is_standard_layout_v<G>;
        // 8. Its state can be saved and restored.
        requires Concept::StreamIOable<G>;
        // 9. Extra requirements.
        requires std::derived_from<G, UniformPseudoRandomBitGeneratorBase<G, typename G::ResultType>>;
        requires std::is_final_v<G>;
    };

} // namespace MACE::Math::Random
