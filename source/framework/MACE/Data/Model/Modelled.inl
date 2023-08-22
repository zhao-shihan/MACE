namespace MACE::Data::inline Model {

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
constexpr auto Modelled<ADerived,
                         std::tuple<ABaseFieldSets...>,
                         std::tuple<ANewFieldSets...>>::Name() -> std::string_view {
    static_assert(std::derived_from<ADerived, Modelled<ADerived,
                                                        std::tuple<ABaseFieldSets...>,
                                                        std::tuple<ANewFieldSets...>>>);
    static_assert(DataModel<ADerived>);
    return ADerived::BasicName();
}

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
constexpr Modelled<ADerived,
                    std::tuple<ABaseFieldSets...>,
                    std::tuple<ANewFieldSets...>>::Entry::~Entry() = default;

#define MACE_DATA_MODEL_MODEL_BASE_ENTRY_GET_IMPL_BODY                                                    \
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
constexpr auto Modelled<ADerived,
                         std::tuple<ABaseFieldSets...>,
                         std::tuple<ANewFieldSets...>>::Entry::GetImpl() const -> decltype(auto) {
    MACE_DATA_MODEL_MODEL_BASE_ENTRY_GET_IMPL_BODY
}

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
template<typename F, gsl::index IFieldSet>
constexpr auto Modelled<ADerived,
                         std::tuple<ABaseFieldSets...>,
                         std::tuple<ANewFieldSets...>>::Entry::GetImpl() -> decltype(auto) {
    MACE_DATA_MODEL_MODEL_BASE_ENTRY_GET_IMPL_BODY
}

#undef MACE_DATA_MODEL_MODEL_BASE_ENTRY_GET_IMPL_BODY

} // namespace MACE::Data::inline Model
