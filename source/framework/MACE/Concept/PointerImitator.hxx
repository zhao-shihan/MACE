#pragma once

#include "MACE/Concept/Indirectable.hxx"
#include "MACE/Concept/Pointer.hxx"
#include "MACE/Concept/PointerAccessible.hxx"
#include "MACE/Concept/Subscriptable.hxx"

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

template<typename P, typename T>
concept WeakPointerImitatorOf =
    requires {
        requires WeaklyIndirectableTo<P, T>;
        requires PointerAccessibleTo<P, T>;
    };

template<typename P, typename T>
concept PointerImitatorOf =
    requires {
        requires WeakPointerImitatorOf<P, T>;
        requires WeaklySubscriptableTo<P, T>;
    };

#include "MACE/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(WeakPointerImitatorOf)
MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerImitatorOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(WeakPointerImitatorOf)
MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerImitatorOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(WeakPointerImitatorOf)
MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerImitatorOf)
#undef MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Concept
