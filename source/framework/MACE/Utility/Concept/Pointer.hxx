#pragma once

#include "MACE/Utility/Concept/detail/IsPointer.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept Indirectable = requires(T&& pointer) {
    *pointer;
};

template<typename T>
concept PointerAccessible = IsPointer<T> or requires(T&& pointer) {
    pointer.operator->();
};

template<typename T>
concept Subscriptable = requires(T&& pointer, std::ptrdiff_t i) {
    pointer[i];
};

template<typename T>
concept WeaklyBehaveLikePointer = requires {
    requires Indirectable<T>;
    requires PointerAccessible<T>;
};

template<typename T>
concept BehaveLikePointer = requires {
    requires WeaklyBehaveLikePointer<T>;
    requires Subscriptable<T>;
};

template<typename P, typename T>
concept IsPointerOf = requires {
    requires std::same_as<std::remove_pointer_t<P>, T>;
    requires std::same_as<P, std::add_pointer_t<T>>;
};

template<typename P, typename T>
concept IndirectableTo = requires(P&& pointer) {
    { *pointer } -> std::same_as<std::add_lvalue_reference_t<T>>;
};

template<typename P, typename T>
concept PointerAccessibleTo = IsPointerOf<P, T> or requires(P&& pointer) {
    { pointer.operator->() } -> std::same_as<std::add_pointer_t<T>>;
};

template<typename P, typename T>
concept SubscriptableTo = requires(P&& pointer, std::ptrdiff_t i) {
    { pointer[i] } -> std::same_as<std::add_lvalue_reference_t<T>>;
};

template<typename P, typename T>
concept WeaklyBehaveLikePointerOf = requires(P&& pointer) {
    requires IndirectableTo<P, T>;
    requires PointerAccessibleTo<P, T>;
};

template<typename P, typename T>
concept BehaveLikePointerOf = requires(P&& pointer, std::ptrdiff_t i) {
    requires WeaklyBehaveLikePointerOf<P, T>;
    requires SubscriptableTo<P, T>;
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

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(MotherConcept) \
    template<typename P, typename T>                                        \
    concept MotherConcept##MaybeConst =                                     \
        MotherConcept<P, std::add_const_t<T>> or                            \
        MotherConcept<P, T> or                                              \
        MotherConcept<P, std::remove_const_t<T>>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(IndirectableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(PointerAccessibleTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(SubscriptableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                           \
    concept MotherConcept##MaybeVolatile =                                     \
        MotherConcept<P, std::add_volatile_t<T>> or                            \
        MotherConcept<P, T> or                                                 \
        MotherConcept<P, std::remove_volatile_t<T>>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(IndirectableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(PointerAccessibleTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(SubscriptableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                                 \
    concept MotherConcept##MaybeConstVolatile = requires {                           \
        requires MotherConcept<P, std::add_cv_t<T>>;                                 \
        requires not MotherConcept<P, std::add_const_t<T>>;                          \
        requires not MotherConcept<P, std::add_volatile_t<T>>;                       \
    }                                                                                \
    or MotherConcept<P, T> or requires {                                             \
        requires MotherConcept<P, std::remove_cv_t<T>>;                              \
        requires not MotherConcept<P, std::remove_const_t<T>>;                       \
        requires not MotherConcept<P, std::remove_volatile_t<T>>;                    \
    }
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(IndirectableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(PointerAccessibleTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(SubscriptableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                                    \
    concept MotherConcept##MaybeConstOrVolatile =                                       \
        MotherConcept##MaybeConst<P, T> or                                              \
        MotherConcept##MaybeVolatile<P, T>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(IsPointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(PointerAccessibleTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(SubscriptableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(IndirectableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(MotherConcept) \
    template<typename P, typename T>                                            \
    concept MotherConcept##MaybeQualified =                                     \
        MotherConcept##MaybeConstOrVolatile<P, T> or                            \
        MotherConcept##MaybeConstVolatile<P, T>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(IsPointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(PointerAccessibleTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(SubscriptableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(IndirectableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED

} // namespace MACE::Utility::Concept
