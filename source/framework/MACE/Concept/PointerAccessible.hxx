#pragma once

#include "MACE/Concept/Pointer.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename P>
concept PointerAccessible =
    std::is_pointer_v<P> or
    requires(P p) {
        p.operator->();
    };

template<typename P, typename T>
concept PointerAccessibleTo =
    PointerOf<P, T> or
    requires(P p) {
        { p.operator->() } -> std::same_as<std::add_pointer_t<T>>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerAccessibleTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerAccessibleTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerAccessibleTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
