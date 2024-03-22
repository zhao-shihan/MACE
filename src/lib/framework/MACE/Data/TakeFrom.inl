namespace MACE::Data {

template<TupleModelizable... Ts>
auto Take<Ts...>::From(ROOT::RDF::RNode rdf) -> std::vector<std::unique_ptr<Tuple<Ts...>>> {
    std::vector<std::unique_ptr<Tuple<Ts...>>> data;
    rdf.Foreach(TakeOne{data, gslx::make_index_sequence<Tuple<Ts...>::Size()>{}},
                []<gsl::index... Is>(gslx::index_sequence<Is...>) -> std::vector<std::string> {
                    return {std::tuple_element_t<Is, Tuple<Ts...>>::Name()...};
                }(gslx::make_index_sequence<Tuple<Ts...>::Size()>{}));
    return data;
}

template<TupleModelizable... Ts>
template<gsl::index... Is>
Take<Ts...>::TakeOne<Is...>::TakeOne(std::vector<std::unique_ptr<Tuple<Ts...>>>& data, gslx::index_sequence<Is...>) :
    fData{data} {}

template<TupleModelizable... Ts>
template<gsl::index... Is>
auto Take<Ts...>::TakeOne<Is...>::operator()(const ReadType<Is>&... value) -> void {
    fData.emplace_back(std::make_unique<Tuple<Ts...>>(value...));
}

} // namespace MACE::Data
