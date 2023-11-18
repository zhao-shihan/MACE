namespace MACE::Data {

template<typename ADerived>
template<gsl::index I>
constexpr auto EnableStructuredBinding<ADerived>::GetImpl() const& -> const Type<I>& {
    static_assert(std::derived_from<ADerived, EnableStructuredBinding>);
    static_assert(TupleLike<ADerived>);
    return Self().template Get<std::tuple_element_t<I, typename ADerived::Model::StdTuple>::Name()>();
}

template<typename ADerived>
template<gsl::index I>
constexpr auto EnableStructuredBinding<ADerived>::GetImpl() & -> Type<I>& {
    static_assert(std::derived_from<ADerived, EnableStructuredBinding>);
    static_assert(TupleLike<ADerived>);
    return Self().template Get<std::tuple_element_t<I, typename ADerived::Model::StdTuple>::Name()>();
}

template<typename ADerived>
template<gsl::index I>
constexpr auto EnableStructuredBinding<ADerived>::GetImpl() && -> Type<I>&& {
    static_assert(std::derived_from<ADerived, EnableStructuredBinding>);
    static_assert(TupleLike<ADerived>);
    return std::move(Self()).template Get<std::tuple_element_t<I, typename ADerived::Model::StdTuple>::Name()>();
}

template<typename ADerived>
template<gsl::index I>
constexpr auto EnableStructuredBinding<ADerived>::GetImpl() const&& -> const Type<I>&& {
    static_assert(std::derived_from<ADerived, EnableStructuredBinding>);
    static_assert(TupleLike<ADerived>);
    return std::move(Self()).template Get<std::tuple_element_t<I, typename ADerived::Model::StdTuple>::Name()>();
}

template<TupleModelizable... Ts>
constexpr Tuple<Ts...>::Tuple(std::convertible_to<Ts> auto&&... values) :
    fTuple{std::forward<decltype(values)>(values)...} {}

template<TupleModelizable... Ts>
constexpr Tuple<Ts...>::Tuple(const typename std::conditional_t<requires { typename Ts::Type; }, Ts, Dummy>::Type&... values) :
    fTuple{values...} {}

template<TupleModelizable... Ts>
constexpr Tuple<Ts...>::Tuple(typename std::conditional_t<requires { typename Ts::Type; }, Ts, Dummy>::Type&&... values) :
    fTuple{std::move(values)...} {}

template<TupleModelizable... Ts>
template<TupleLike ATuple>
constexpr auto Tuple<Ts...>::operator==(const ATuple& that) const -> auto {
    if constexpr (not TupleEquivalent<Tuple, ATuple>) { return false; }
    return [&]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (... and
                ([&]<gsl::index... Js, gsl::index I>(gslx::index_sequence<Js...>, std::integral_constant<gsl::index, I>) {
                    return (... or
                            ([&] {
                                constexpr auto nameI = std::tuple_element_t<I, Tuple>::Name();
                                constexpr auto nameJ = std::tuple_element_t<Js, ATuple>::Name();
                                if constexpr (nameI != nameJ) {
                                    return false;
                                } else {
                                    return Get<nameI>() == that.template Get<nameJ>();
                                }
                            }()));
                }(gslx::make_index_sequence<ATuple::Size()>{}, std::integral_constant<gsl::index, Is>{})));
    }(gslx::make_index_sequence<Size()>{});
}

} // namespace MACE::Data
