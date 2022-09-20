#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept Indirectable = requires(T p) {
    *p;
};

template<typename T, typename U>
concept IndirectableTo = requires(T p) {
    { *p } -> std::same_as<U>;
};

template<typename T, typename U>
concept WeaklyIndirectableTo =
    IndirectableTo<T, std::remove_reference_t<U>> or
    IndirectableTo<T, U> or
    IndirectableTo<T, U&>;

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(IndirectableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(WeaklyIndirectableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(IndirectableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(WeaklyIndirectableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(IndirectableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(WeaklyIndirectableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
