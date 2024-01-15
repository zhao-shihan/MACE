namespace MACE::Data {

template<TupleModelizable... Ts>
Output<Ts...>::Output(const std::string& name, const std::string& title) :
    NonMoveableBase{},
    fTree{name.c_str(), title.c_str()},
    fEntry{},
    fBranchHelper{fEntry} {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (...,
         [this]<gsl::index I>(std::integral_constant<gsl::index, I>) {
             using TheValue = std::tuple_element_t<I, Tuple<Ts...>>;
             const auto branch{fBranchHelper.template CreateBranch<TheValue::Name()>(fTree)};
             branch->SetAutoDelete(false);
             if constexpr (TheValue::Description().HasValue()) {
                 const auto title{fmt::format("({}) {}", branch->GetLeaf(TheValue::Name())->GetTypeName(), TheValue::Description().StringView())};
                 branch->SetTitle(title.c_str());
             }
         }(std::integral_constant<gsl::index, Is>{}));
    }(gslx::make_index_sequence<Tuple<Ts...>::Size()>());
}

template<TupleModelizable... Ts>
template<typename T>
    requires std::assignable_from<Tuple<Ts...>&, T>
auto Output<Ts...>::Fill(T&& tuple) -> std::size_t {
    fEntry = std::forward<T>(tuple);
    return fTree.Fill();
}

template<TupleModelizable... Ts>
template<std::ranges::input_range R>
    requires std::assignable_from<Tuple<Ts...>&, std::ranges::range_reference_t<R>>
auto Output<Ts...>::Fill(R&& data) -> std::size_t {
    std::size_t bytesTotal{};
    for (auto&& tuple : std::forward<R>(data)) {
        bytesTotal += Fill(std23::forward_like<R>(tuple));
    }
    return bytesTotal;
}

template<TupleModelizable... Ts>
template<std::ranges::input_range R>
    requires std::indirectly_readable<std::ranges::range_value_t<R>> and
             std::assignable_from<Tuple<Ts...>&, std::iter_reference_t<std::ranges::range_value_t<R>>>
auto Output<Ts...>::Fill(const R& data) -> std::size_t {
    std::size_t bytesTotal{};
    for (auto&& i : data) {
        bytesTotal += Fill(std::forward<decltype(*i)>(*i));
    }
    return bytesTotal;
}

template<TupleModelizable... Ts>
Output<Ts...>::OutputIterator::OutputIterator(Output* output) :
    fOutput(output) {}

} // namespace MACE::Data
