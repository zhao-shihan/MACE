#pragma once

#include "MACE/Utility/Concept/internal/IsPointer.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Utility::Concept {

template<typename P, typename T>
concept IsPointerOf = requires {
    requires IsPointer<P>;
    requires std::same_as<std::remove_pointer_t<P>, T>;
    requires std::same_as<P, std::add_pointer_t<T>>;
};

#define MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(qualifier)                                                 \
    requires {                                                                                              \
        requires IsPointerOf<P, std::remove_##qualifier##_t<T>>;                                            \
        requires IsPointerOf<std::add_pointer_t<std::add_##qualifier##_t<std::remove_pointer_t<P>>>, T>;    \
    }                                                                                                       \
    or IsPointerOf<P, T> or requires {                                                                      \
        requires IsPointerOf<P, std::add_##qualifier##_t<T>>;                                               \
        requires IsPointerOf<std::add_pointer_t<std::remove_##qualifier##_t<std::remove_pointer_t<P>>>, T>; \
    }

template<typename P, typename T>
concept IsPointerOfMaybeConst = MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(const);

template<typename P, typename T>
concept IsPointerOfMaybeVolatile = MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(volatile);

template<typename P, typename T>
concept IsPointerOfMaybeConstVolatile = MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(cv);

#undef MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE

#include "MACE/Utility/Concept/internal/AccessToMaybeCVConceptMacro.inl"

#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(IsPointerOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(IsPointerOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Utility::Concept
