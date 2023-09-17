namespace MACE::Data::inline Model {

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> ABaseFieldSetTuple,
         Concept::InstantiatedFrom<std::tuple> AThisFieldSetTuple>
constexpr auto Modelize<ADerived,
                        ABaseFieldSetTuple,
                        AThisFieldSetTuple>::Name() -> std::string_view {
    static_assert(std::derived_from<ADerived, Modelize<ADerived,
                                                       ABaseFieldSetTuple,
                                                       AThisFieldSetTuple>>);
    return ADerived::BasicName();
}

} // namespace MACE::Data::inline Model
