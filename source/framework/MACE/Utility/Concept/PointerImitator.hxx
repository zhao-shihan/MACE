#pragma once

#include "MACE/Utility/Concept/Indirectable.hxx"
#include "MACE/Utility/Concept/IsPointer.hxx"
#include "MACE/Utility/Concept/PointerAccessible.hxx"
#include "MACE/Utility/Concept/Subscriptable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept WeakPointerImitator = requires {
    requires Indirectable<T>;
    requires PointerAccessible<T>;
};

template<typename T>
concept PointerImitator = requires {
    requires WeakPointerImitator<T>;
    requires Subscriptable<T>;
};

template<typename P, typename T>
concept WeakPointerImitatorOf = requires(P&& pointer) {
    requires IndirectableTo<P, T>;
    requires PointerAccessibleTo<P, T>;
};

template<typename P, typename T>
concept PointerImitatorOf = requires(P&& pointer) {
    requires WeakPointerImitatorOf<P, T>;
    requires SubscriptableTo<P, std::add_lvalue_reference_t<T>>;
};

#include "MACE/Utility/Concept/internal/AccessToMaybeCVConceptMacro.inl"

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(WeakPointerImitatorOf)
MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(PointerImitatorOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(WeakPointerImitatorOf)
MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(PointerImitatorOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(WeakPointerImitatorOf)
MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(PointerImitatorOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(WeakPointerImitatorOf)
MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(PointerImitatorOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE

MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(WeakPointerImitatorOf)
MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(PointerImitatorOf)
#undef MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED

} // namespace MACE::Utility::Concept
