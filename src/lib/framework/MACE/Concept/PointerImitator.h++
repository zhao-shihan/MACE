#pragma once

#include "MACE/Concept/Indirectable.h++"
#include "MACE/Concept/Pointer.h++"
#include "MACE/Concept/PointerAccessible.h++"
#include "MACE/Concept/Subscriptable.h++"

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept WeakPointerImitator =
    requires {
        requires Indirectable<T>;
        requires PointerAccessible<T>;
    };

template<typename T>
concept PointerImitator =
    requires {
        requires WeakPointerImitator<T>;
        requires Subscriptable<T>;
    };

template<typename T, typename U>
concept WeakPointerImitatorOf =
    requires {
        requires IndirectableToMaybeReferenced<T, U>;
        requires PointerAccessibleTo<T, U>;
    };

template<typename T, typename U>
concept PointerImitatorOf =
    requires {
        requires WeakPointerImitatorOf<T, U>;
        requires SubscriptableToMaybeReferenced<T, U>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

template<typename T, typename U>
concept PointerImitatorOfMaybeConst =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(WeakPointerImitatorOf)

template<typename T, typename U>
concept PointerImitatorOfMaybeConstReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerImitatorOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

template<typename T, typename U>
concept PointerImitatorOfMaybeVolatile =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(WeakPointerImitatorOf)

template<typename T, typename U>
concept PointerImitatorOfMaybeVolatileReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerImitatorOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

template<typename T, typename U>
concept PointerImitatorOfMaybeQualified =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(WeakPointerImitatorOf)

template<typename T, typename U>
concept PointerImitatorOfMaybeQualifyReferenced =
    MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerImitatorOf)

#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
