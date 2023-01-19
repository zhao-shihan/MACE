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
concept WeaklySubscriptableTo =
    SubscriptableTo<T, std::remove_reference_t<U>> or
    SubscriptableTo<T, U> or
    SubscriptableTo<T, U&>;

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(SubscriptableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(WeaklySubscriptableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(SubscriptableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(WeaklySubscriptableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(SubscriptableTo)
MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(WeaklySubscriptableTo)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
