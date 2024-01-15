#pragma once

#include "MACE/Concept/Pointer.h++"

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept PointerAccessible =
    std::is_pointer_v<T> or
    requires(T p) {
        p.operator->();
    };

template<typename T, typename U>
concept PointerAccessibleTo =
    PointerOf<T, U> or
    requires(T p) {
        { p.operator->() } -> std::same_as<std::add_pointer_t<U>>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

template<typename T, typename U>
concept PointerAccessibleToMaybeConst =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerAccessibleTo)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

template<typename T, typename U>
concept PointerAccessibleToMaybeVolatile =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerAccessibleTo)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

template<typename T, typename U>
concept PointerAccessibleToMaybeQualified =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerAccessibleTo)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
