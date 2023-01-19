#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename P, typename T>
concept PointerOf =
    requires {
        requires std::is_pointer_v<P>;
        requires std::same_as<std::remove_pointer_t<P>, std::remove_reference_t<T>>;
        requires std::same_as<P, std::add_pointer_t<T>>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
