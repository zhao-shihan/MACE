#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T, typename U>
concept PointerOf =
    requires {
        requires std::is_pointer_v<T>;
        requires std::same_as<std::remove_pointer_t<T>, std::remove_reference_t<U>>;
        requires std::same_as<T, std::add_pointer_t<U>>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

template<typename T, typename U>
concept PointerOfMaybeConst =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

template<typename T, typename U>
concept PointerOfMaybeVolatile =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

template<typename T, typename U>
concept PointerOfMaybeQualified =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
