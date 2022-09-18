#pragma once

#include "MACE/Concept/IsPointer.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept PointerAccessible = IsPointer<T> or requires(T&& pointer) {
    pointer.operator->();
};

template<typename P, typename T>
concept PointerAccessibleTo = IsPointerOf<P, T> or requires(P&& pointer) {
    { pointer.operator->() } -> std::same_as<std::add_pointer_t<T>>;
};

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerAccessibleTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerAccessibleTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(PointerAccessibleTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(PointerAccessibleTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerAccessibleTo)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
