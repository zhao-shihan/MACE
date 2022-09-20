#define MACE_CONCEPT_ACCESS_TO_MAYBE_CONST(MotherConcept) \
    template<typename P, typename T>                      \
    concept MotherConcept##MaybeConst =                   \
        MotherConcept<P, T> or                            \
        MotherConcept<P, const T>;

#define MACE_CONCEPT_ACCESS_TO_MAYBE_VOLATILE(MotherConcept) \
    template<typename P, typename T>                         \
    concept MotherConcept##MaybeVolatile =                   \
        MotherConcept<P, T> or                               \
        MotherConcept<P, volatile T>;

#define MACE_CONCEPT_ACCESS_TO_MAYBE_QUALIFIED(MotherConcept) \
    template<typename P, typename T>                          \
    concept MotherConcept##MaybeQualified =                   \
        MotherConcept<P, T> or                                \
        MotherConcept<P, const T> or                          \
        MotherConcept<P, volatile T> or                       \
        MotherConcept<P, const volatile T>;
