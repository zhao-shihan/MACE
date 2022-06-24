#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept IsPointer =
    std::is_pointer_v<T>;

template<typename T>
concept Dereferenceable = requires(T&& pointer) {
    *pointer;
};

template<typename T>
concept WeaklyBehaveLikePointer = requires(T&& pointer, std::ptrdiff_t i) {
    requires Dereferenceable<T>;
    pointer[i];
};

template<typename P, typename T>
concept BehaveLikePointer = requires(P&& pointer) {
    requires WeaklyBehaveLikePointer<T>;
    pointer.operator->();
};

template<typename P, typename T>
concept IsPointerOf =
    std::same_as<std::remove_pointer_t<P>, T> and
    std::same_as<P, std::add_pointer_t<T>>;

template<typename P, typename T>
concept DereferenceableTo = requires(P&& pointer) {
    { *pointer } -> std::same_as<std::add_lvalue_reference_t<T>>;
};

template<typename P, typename T>
concept WeaklyBehaveLikePointerOf = requires(P&& pointer, std::ptrdiff_t i) {
    requires DereferenceableTo<P, T>;
    { pointer[i] } -> std::same_as<std::add_lvalue_reference_t<T>>;
};

template<typename P, typename T>
concept BehaveLikePointerOf = requires(P&& pointer) {
    requires WeaklyBehaveLikePointerOf<P, T>;
    { pointer.operator->() } -> std::same_as<std::add_pointer_t<T>>;
};

#define MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(stdTypeTraitsQualifier)                                     \
    (IsPointerOf<P, std::remove_##stdTypeTraitsQualifier##_t<T>> and                                         \
     IsPointerOf<std::add_pointer_t<std::add_##stdTypeTraitsQualifier##_t<std::remove_pointer_t<P>>>, T>) or \
        IsPointerOf<P, T> or                                                                                 \
        (IsPointerOf<P, std::add_##stdTypeTraitsQualifier##_t<T>> and                                        \
         IsPointerOf<std::add_pointer_t<std::remove_##stdTypeTraitsQualifier##_t<std::remove_pointer_t<P>>>, T>)
template<typename P, typename T>
concept IsPointerOfMaybeConst =
    MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(const);
template<typename P, typename T>
concept IsPointerOfMaybeVolatile =
    MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(volatile);
template<typename P, typename T>
concept IsPointerOfMaybeConstVolatile =
    MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE(cv);
#undef MACE_UTILITY_CONCEPT_IS_POINTER_OF_MAYBE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(MotherConcept) \
    template<typename P, typename T>                                        \
    concept MotherConcept##MaybeConst =                                     \
        MotherConcept<P, std::add_const_t<T>> or                            \
        MotherConcept<P, T> or                                              \
        MotherConcept<P, std::remove_const_t<T>>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(DereferenceableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                           \
    concept MotherConcept##MaybeVolatile =                                     \
        MotherConcept<P, std::add_volatile_t<T>> or                            \
        MotherConcept<P, T> or                                                 \
        MotherConcept<P, std::remove_volatile_t<T>>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(DereferenceableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                                 \
    concept MotherConcept##MaybeConstVolatile =                                      \
        (MotherConcept<P, std::add_cv_t<T>> and                                      \
         not MotherConcept<P, std::add_const_t<T>> and                               \
         not MotherConcept<P, std::add_volatile_t<T>>) or                            \
        MotherConcept<P, T> or                                                       \
        (MotherConcept<P, std::remove_cv_t<T>> and                                   \
         not MotherConcept<P, std::remove_const_t<T>> and                            \
         not MotherConcept<P, std::remove_volatile_t<T>>)
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(DereferenceableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                                    \
    concept MotherConcept##MaybeConstOrVolatile =                                       \
        MotherConcept##MaybeConst<P, T> or                                              \
        MotherConcept##MaybeVolatile<P, T>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(IsPointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(DereferenceableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_CONST_OR_VOLATILE

#define MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(MotherConcept) \
    template<typename P, typename T>                                            \
    concept MotherConcept##MaybeQualified =                                     \
        MotherConcept##MaybeConstOrVolatile<P, T> or                            \
        MotherConcept##MaybeConstVolatile<P, T>
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(IsPointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(DereferenceableTo);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(WeaklyBehaveLikePointerOf);
MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED(BehaveLikePointerOf);
#undef MACE_UTILITY_CONCEPT_POINTER_ANALOGUE_OF_MAYBE_QUALIFIED

} // namespace MACE::Utility::Concept
