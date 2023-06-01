#pragma once

#include "gsl/gsl"

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept Subscriptable =
    requires(T v, gsl::index i) {
        v[i];
    };

template<typename T, typename U>
concept SubscriptableTo =
    requires(T v, gsl::index i) {
        { v[i] } -> std::same_as<U>;
    };

template<typename T, typename U>
concept SubscriptableToMaybeReferenced =
    SubscriptableTo<T, std::remove_reference_t<U>> or
    SubscriptableTo<T, U> or
    SubscriptableTo<T, U&>;

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

template<typename T, typename U>
concept SubscriptableToMaybeConst =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(SubscriptableTo)

template<typename T, typename U>
concept SubscriptableToMaybeConstReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(SubscriptableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

template<typename T, typename U>
concept SubscriptableToMaybeVolatile =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(SubscriptableTo)

template<typename T, typename U>
concept SubscriptableToMaybeVolatileReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(SubscriptableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

template<typename T, typename U>
concept SubscriptableToMaybeQualified =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(SubscriptableTo)

template<typename T, typename U>
concept SubscriptableToMaybeQualifyReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(SubscriptableToMaybeReferenced)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
