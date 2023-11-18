namespace MACE::Data {

template<TupleModelizable... Ts>
Writer<Ts...>::Writer(const std::string& name, const std::string& title) :
    NonMoveableBase{},
    fTree{name.c_str(), title.c_str()},
    fEntry{},
    fBranchAddressHelper{} {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (...,
         [this] {
             using TheValue = std::tuple_element_t<Is, Tuple<Ts...>>;
             const auto branch = fTree.Branch(TheValue::Name(), fBranchAddressHelper.template ValuePointer<TheValue::Name()>(fEntry));
             branch->SetAutoDelete(false);
             if constexpr (TheValue::Description().HasValue()) {
                 const auto title = fmt::format("({}) {}", branch->GetLeaf(TheValue::Name())->GetTypeName(), TheValue::Description().StringView());
                 branch->SetTitle(title.c_str());
             }
         }());
    }(gslx::make_index_sequence<Tuple<Ts...>::Size()>());
}

template<TupleModelizable... Ts>
template<typename T>
    requires std::assignable_from<Tuple<Ts...>&, T>
auto Writer<Ts...>::Fill(T&& tuple) -> std::size_t {
    fEntry = std::forward<T>(tuple);
    return fTree.Fill();
}

template<TupleModelizable... Ts>
template<std::ranges::input_range R>
    requires std::assignable_from<Tuple<Ts...>&, std::ranges::range_reference_t<R>>
auto Writer<Ts...>::Fill(R&& data) -> std::size_t {
    std::size_t bytesTotal{};
    for (auto&& tuple : std::forward<R>(data)) {
        bytesTotal += Fill(std::forward_like<R>(tuple));
    }
    return bytesTotal;
}

template<TupleModelizable... Ts>
template<std::ranges::input_range R>
    requires std::indirectly_readable<std::ranges::range_value_t<R>> and
             std::assignable_from<Tuple<Ts...>&, std::iter_reference_t<std::ranges::range_value_t<R>>>
auto Writer<Ts...>::Fill(const R& data) -> std::size_t {
    std::size_t bytesTotal{};
    for (auto&& i : data) {
        bytesTotal += Fill(std::forward<decltype(*i)>(*i));
    }
    return bytesTotal;
}

template<TupleModelizable... Ts>
Writer<Ts...>::WriteIterator::WriteIterator(Writer* writer) :
    fWriter(writer) {}

} // namespace MACE::Data
