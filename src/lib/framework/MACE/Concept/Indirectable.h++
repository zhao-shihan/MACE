#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept Indirectable =
    requires(T p) {
        *p;
    };

template<typename T, typename U>
concept IndirectableTo =
    requires(T p) {
        { *p } -> std::same_as<U>;
    };

template<typename T, typename U>
concept IndirectableToMaybeReferenced =
    IndirectableTo<T, std::remove_reference_t<U>> or
    IndirectableTo<T, U> or
    IndirectableTo<T, U&>;

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

template<typename T, typename U>
concept IndirectableToMaybeConst =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(IndirectableTo)

template<typename T, typename U>
concept IndirectableToMaybeConstReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(IndirectableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

template<typename T, typename U>
concept IndirectableToMaybeVolatile =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(IndirectableTo)

template<typename T, typename U>
concept IndirectableToMaybeVolatileReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(IndirectableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

template<typename T, typename U>
concept IndirectableToMaybeQualified =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(IndirectableTo)

template<typename T, typename U>
concept IndirectableToMaybeQualifyReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(IndirectableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
