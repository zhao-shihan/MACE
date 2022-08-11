#define MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST(MotherConcept) \
    template<typename P, typename T>                              \
    concept MotherConcept##MaybeConst =                           \
        MotherConcept<P, std::add_const_t<T>> or                  \
        MotherConcept<P, T> or                                    \
        MotherConcept<P, std::remove_const_t<T>>;

#define MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                 \
    concept MotherConcept##MaybeVolatile =                           \
        MotherConcept<P, std::add_volatile_t<T>> or                  \
        MotherConcept<P, T> or                                       \
        MotherConcept<P, std::remove_volatile_t<T>>;

#define MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                       \
    concept MotherConcept##MaybeConstVolatile = requires {                 \
        requires MotherConcept<P, std::add_cv_t<T>>;                       \
        requires not MotherConcept<P, std::add_const_t<T>>;                \
        requires not MotherConcept<P, std::add_volatile_t<T>>;             \
    }                                                                      \
    or MotherConcept<P, T> or requires {                                   \
        requires MotherConcept<P, std::remove_cv_t<T>>;                    \
        requires not MotherConcept<P, std::remove_const_t<T>>;             \
        requires not MotherConcept<P, std::remove_volatile_t<T>>;          \
    };

#define MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_CONST_OR_VOLATILE(MotherConcept) \
    template<typename P, typename T>                                          \
    concept MotherConcept##MaybeConstOrVolatile =                             \
        MotherConcept##MaybeConst<P, T> or                                    \
        MotherConcept##MaybeVolatile<P, T>;

#define MACE_UTILITY_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(MotherConcept) \
    template<typename P, typename T>                                  \
    concept MotherConcept##MaybeQualified =                           \
        MotherConcept##MaybeConstOrVolatile<P, T> or                  \
        MotherConcept##MaybeConstVolatile<P, T>;
