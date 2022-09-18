#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept Indirectable = requires(T&& p) {
    *p;
};

template<typename P, typename T>
concept IndirectableTo = requires(P&& p) {
    { *p } -> std::same_as<std::add_lvalue_reference_t<T>>;
};

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(IndirectableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(IndirectableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(IndirectableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(IndirectableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(IndirectableTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
