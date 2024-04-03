#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/CETAString.h++"

#include "gsl/gsl"

#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

namespace MACE::Data {

template<typename T>
concept TupleLike = requires {
    typename T::Model;
    requires Concept::InstantiatedFrom<typename T::Model, TupleModel>;
    { T::Size() } -> std::same_as<std::size_t>;
    requires T::Size() >= 0;
    requires([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (... and requires(T t) { t.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name()>(); });
    }(gslx::make_index_sequence<T::Size()>{}));
    requires([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (... and requires(const T t) { t.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name()>(); });
    }(gslx::make_index_sequence<T::Size()>{}));
    requires T::Size() <= 1 or requires {
        requires([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and requires(T t) { t.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name(),
                                                           std::tuple_element_t<Is + 1, typename T::Model::StdTuple>::Name()>(); });
        }(gslx::make_index_sequence<T::Size() - 1>{}));
        requires([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and requires(const T t) { t.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name(),
                                                                 std::tuple_element_t<Is + 1, typename T::Model::StdTuple>::Name()>(); });
        }(gslx::make_index_sequence<T::Size() - 1>{}));
    };
};

template<typename I1, typename I2>
concept TupleContain = requires {
    requires TupleLike<I1>;
    requires TupleLike<I2>;
    requires TupleModelContain<typename I1::Model, typename I2::Model>;
};

template<typename I1, typename I2>
concept TupleEquivalent = requires {
    requires TupleContain<I1, I2>;
    requires TupleContain<I2, I1>;
};

} // namespace MACE::Data

namespace std {

template<typename T>
    requires requires { typename T::Model; } and
             MACE::Concept::InstantiatedFrom<typename T::Model, MACE::Data::TupleModel>
struct tuple_size<T>
    : tuple_size<typename T::Model::StdTuple> {};

template<std::size_t I, typename T>
    requires requires { typename T::Model; } and
             MACE::Concept::InstantiatedFrom<typename T::Model, MACE::Data::TupleModel>
struct tuple_element<I, T>
    : tuple_element<I, typename T::Model::StdTuple> {};

} // namespace std

namespace MACE::Data {

template<typename ADerived>
class EnableGet {
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    friend constexpr auto Get(const ADerived& t) -> decltype(auto) { return t.template Get<ANames...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    friend constexpr auto Get(ADerived& t) -> decltype(auto) { return t.template Get<ANames...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    friend constexpr auto Get(ADerived&& t) -> decltype(auto) { return std::move(t).template Get<ANames...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    friend constexpr auto Get(const ADerived&& t) -> decltype(auto) { return std::move(t).template Get<ANames...>(); }

    template<gsl::index I>
    friend constexpr auto get(const ADerived& t) -> decltype(auto) { return t.template Get<std::tuple_element_t<I, ADerived>::Name()>(); }
    template<gsl::index I>
    friend constexpr auto get(ADerived& t) -> decltype(auto) { return t.template Get<std::tuple_element_t<I, ADerived>::Name()>(); }
    template<gsl::index I>
    friend constexpr auto get(ADerived&& t) -> decltype(auto) { return std::move(t).template Get<std::tuple_element_t<I, ADerived>::Name()>(); }
    template<gsl::index I>
    friend constexpr auto get(const ADerived&& t) -> decltype(auto) { return std::move(t).template Get<std::tuple_element_t<I, ADerived>::Name()>(); }

protected:
    constexpr EnableGet();
    constexpr ~EnableGet() = default;
};

template<TupleModelizable... Ts>
class Tuple : public EnableGet<Tuple<Ts...>> {
public:
    using Model = TupleModel<Ts...>;

private:
    struct Dummy {
        using Type = Dummy;
    };

public:
    constexpr Tuple() = default;

    template<typename... Us>
        requires(sizeof...(Us) == Model::Size() and
                 []<gsl::index... Is>(gslx::index_sequence<Is...>) {
                     return (... and std::constructible_from<std::tuple_element_t<Is, typename Model::StdTuple>,
                                                             std::tuple_element_t<Is, std::tuple<Us...>>&&>);
                 }(gslx::make_index_sequence<sizeof...(Us)>()))
    constexpr explicit(sizeof...(Us) == 1) Tuple(Us&&... values) :
        fTuple{std::forward<Us>(values)...} {}

    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() const& -> decltype(auto) { return GetImpl<Model::template Index<ANames>()...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() & -> decltype(auto) { return GetImpl<Model::template Index<ANames>()...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() && -> decltype(auto) { return std::move(*this).template GetImpl<Model::template Index<ANames>()...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() const&& -> decltype(auto) { return std::move(*this).template GetImpl<Model::template Index<ANames>()...>(); }

    template<TupleLike ATuple>
    constexpr auto operator==(const ATuple& that) const -> auto;
    template<TupleLike ATuple>
    constexpr auto operator<=>(const ATuple&) const -> auto = delete;

    static constexpr auto Size() -> auto { return Model::Size(); }

private:
    template<gsl::index I>
        requires(0 <= I and I < Model::Size())
    constexpr auto GetImpl() const& -> const std::tuple_element_t<I, Tuple>& { return std::get<I>(fTuple); }
    template<gsl::index I>
        requires(0 <= I and I < Model::Size())
    constexpr auto GetImpl() & -> std::tuple_element_t<I, Tuple>& { return std::get<I>(fTuple); }
    template<gsl::index I>
        requires(0 <= I and I < Model::Size())
    constexpr auto GetImpl() && -> std::tuple_element_t<I, Tuple>&& { return std::get<I>(std::move(fTuple)); }
    template<gsl::index I>
        requires(0 <= I and I < Model::Size())
    constexpr auto GetImpl() const&& -> const std::tuple_element_t<I, Tuple>&& { return std::get<I>(std::move(fTuple)); }

    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::Size()))
    constexpr auto GetImpl() const& -> auto { return Tuple<std::tuple_element_t<Is, Tuple>...>{std::get<Is>(fTuple)...}; }
    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::Size()))
    constexpr auto GetImpl() && -> auto { return Tuple<std::tuple_element_t<Is, Tuple>...>{std::get<Is>(std::move(fTuple))...}; }
    template<gsl::index... Is>
        requires((sizeof...(Is) >= 2) and ... and (0 <= Is and Is < Model::Size()))
    constexpr auto GetImpl() const&& -> auto { return Tuple<std::tuple_element_t<Is, Tuple>...>{std::get<Is>(std::move(fTuple))...}; }

private:
    typename Model::StdTuple fTuple;
};

template<typename... Ts>
Tuple(Ts...) -> Tuple<Ts...>;

} // namespace MACE::Data

#include "MACE/Data/Tuple.inl"
