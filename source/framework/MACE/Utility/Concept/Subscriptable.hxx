#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept Subscriptable = requires(T&& v, std::ptrdiff_t i) {
    v[i];
};

template<typename T, typename U>
concept SubscriptableTo = requires(T&& v, std::ptrdiff_t i) {
    { v[i] } -> std::same_as<U>;
};

#include "MACE/Utility/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(SubscriptableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(SubscriptableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(SubscriptableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(SubscriptableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(SubscriptableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Utility::Concept
