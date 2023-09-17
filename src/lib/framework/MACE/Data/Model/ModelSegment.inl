namespace MACE::Data::inline Model {

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
constexpr ModelSegment<ADerived,
                       std::tuple<ABaseFieldSets...>,
                       std::tuple<ANewFieldSets...>>::Entry::~Entry() = default;

#define MACE_DATA_MODEL_UNNAMED_MODELIZE_ENTRY_GET_IMPL_BODY                                              \
    static_assert(std::derived_from<ADerived, ModelSegment<ADerived,                                      \
                                                           std::tuple<ABaseFieldSets...>,                 \
                                                           std::tuple<ANewFieldSets...>>>);               \
    using TheFieldSet = std::tuple_element_t<IFieldSet, std::tuple<ABaseFieldSets..., ANewFieldSets...>>; \
    if constexpr (stdx::tuple_contains_unique_v<typename TheFieldSet::FieldTuple, F>) {                   \
        return TheFieldSet::Entry::template Get<F>();                                                     \
    } else {                                                                                              \
        return GetImpl<F, IFieldSet + 1>();                                                               \
    }

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
template<typename F, gsl::index IFieldSet>
constexpr auto ModelSegment<ADerived,
                            std::tuple<ABaseFieldSets...>,
                            std::tuple<ANewFieldSets...>>::Entry::GetImpl() const -> decltype(auto) {
    MACE_DATA_MODEL_UNNAMED_MODELIZE_ENTRY_GET_IMPL_BODY
}

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
template<typename F, gsl::index IFieldSet>
constexpr auto ModelSegment<ADerived,
                            std::tuple<ABaseFieldSets...>,
                            std::tuple<ANewFieldSets...>>::Entry::GetImpl() -> decltype(auto) {
    MACE_DATA_MODEL_UNNAMED_MODELIZE_ENTRY_GET_IMPL_BODY
}

#undef MACE_DATA_MODEL_UNNAMED_MODELIZE_ENTRY_GET_IMPL_BODY

} // namespace MACE::Data::inline Model
