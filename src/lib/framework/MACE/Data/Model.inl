namespace MACE::Data::internal {

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> AFieldTuple>
constexpr auto ModelBase<ADerived, AFieldTuple>::Name() {
    return
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return std::tie(Field<Is>::Name()...);
        }(gslx::make_index_sequence<NField()>{});
}

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> AFieldTuple>
constexpr auto ModelBase<ADerived, AFieldTuple>::Title() {
    return
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return std::tie(Field<Is>::Title()...);
        }(gslx::make_index_sequence<NField()>{});
}

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> AFieldTuple>
template<CEvalNTSTA AName, gsl::index I>
constexpr auto ModelBase<ADerived, AFieldTuple>::IndexImpl() {
    static_assert(I >= 0, "no such field of this name within this data model");
    if constexpr (Name<I>() == AName) {
        return I;
    } else {
        return IndexImpl<AName, I - 1>();
    }
}

} // namespace MACE::Data::internal
