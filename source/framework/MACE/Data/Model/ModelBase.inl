namespace MACE::Data::inline Model {

template<class ADerived,
         Concept::InstantiatedFrom<FieldSet>... ABaseFieldSets,
         Concept::InstantiatedFrom<FieldSet>... ANewFieldSets>
constexpr auto ModelBase<ADerived,
                         std::tuple<ABaseFieldSets...>,
                         std::tuple<ANewFieldSets...>>::Name() -> std::string_view {
    static_assert(std::derived_from<ADerived, ModelBase<ADerived,
                                                        std::tuple<ABaseFieldSets...>,
                                                        std::tuple<ANewFieldSets...>>>);
    static_assert(DataModel<ADerived>);
    return ADerived::BasicName();
}

template<class ADerived,
         Concept::InstantiatedFrom<FieldSet>... ABaseFieldSets,
         Concept::InstantiatedFrom<FieldSet>... ANewFieldSets>
constexpr ModelBase<ADerived,
                    std::tuple<ABaseFieldSets...>,
                    std::tuple<ANewFieldSets...>>::Entry::~Entry() = default;

} // namespace MACE::Data::inline Model
