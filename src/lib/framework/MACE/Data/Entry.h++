#pragma once

#include "MACE/Data/CEvalNTSTA.h++"
#include "MACE/Data/Model.h++"

#include "gsl/gsl"

#include <tuple>

namespace MACE::Data {

template<Modelizable... Ts>
struct Entry final : Model<Ts...>::FieldTuple {
public:
    using Model = Model<Ts...>;

public:
    template<CEvalNTSTA... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() & -> decltype(auto) { return Get<Model::template Index<ANames>()...>(); }
    template<CEvalNTSTA... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() const& -> decltype(auto) { return Get<Model::template Index<ANames>()...>(); }
    template<CEvalNTSTA... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() && -> decltype(auto) { return std::tuple{std::get<Model::template Index<ANames>()>(std::move(*this))...}; }

    template<gsl::index I>
        requires(0 <= I and I < Model::NField())
    constexpr auto Get() & -> decltype(auto) { return std::get<I>(*this); }
    template<gsl::index I>
        requires(0 <= I and I < Model::NField())
    constexpr auto Get() const& -> decltype(auto) { return std::get<I>(*this); }
    template<gsl::index I>
        requires(0 <= I and I < Model::NField())
    constexpr auto Get() && -> decltype(auto) { return std::get<I>(std::move(*this)); }
    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::NField()))
    constexpr auto Get() & { return std::tie(std::get<Is>(*this)...); }
    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::NField()))
    constexpr auto Get() const& { return std::tie(std::get<Is>(*this)...); }
    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::NField()))
    constexpr auto Get() && { return std::tuple{std::get<Is>(std::move(*this))...}; }
};

} // namespace MACE::Data

namespace std {

template<MACE::Data::Modelizable... Ts>
struct tuple_size<MACE::Data::Entry<Ts...>>
    : std::integral_constant<std::size_t, MACE::Data::Model<Ts...>::NField()> {};

template<std::size_t I, MACE::Data::Modelizable... Ts>
struct tuple_element<I, MACE::Data::Entry<Ts...>> {
    using type = typename MACE::Data::Model<Ts...>::template Field<I>;
};

} // namespace std
