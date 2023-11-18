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
concept TupleLike = requires(T i, const T ci) {
    typename T::Model;
    requires Concept::InstantiatedFrom<typename T::Model, TupleModel>;
    { T::Size() } -> std::same_as<std::size_t>;
    requires T::Size() >= 0;
    {
        []<gsl::index... Is>(gslx::index_sequence<Is...>, T tuple) {
            (..., (std::ignore = tuple.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name()>()));
        }(gslx::make_index_sequence<T::Size()>{}, i)
    };
    {
        []<gsl::index... Is>(gslx::index_sequence<Is...>, const T tuple) {
            (..., (std::ignore = tuple.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name()>()));
        }(gslx::make_index_sequence<T::Size()>{}, ci)
    };
    requires T::Size() <= 1 or requires {
        {
            []<gsl::index... Is>(gslx::index_sequence<Is...>, T tuple) {
                (..., (std::ignore = tuple.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name(),
                                                        std::tuple_element_t<Is + 1, typename T::Model::StdTuple>::Name()>()));
            }(gslx::make_index_sequence<T::Size() - 1>{}, i)
        };
        {
            []<gsl::index... Is>(gslx::index_sequence<Is...>, const T tuple) {
                (..., (std::ignore = tuple.template Get<std::tuple_element_t<Is, typename T::Model::StdTuple>::Name(),
                                                        std::tuple_element_t<Is + 1, typename T::Model::StdTuple>::Name()>()));
            }(gslx::make_index_sequence<T::Size() - 1>{}, ci)
        };
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
class EnableStructuredBinding {
private:
    template<gsl::index I>
    using Type = std::tuple_element_t<I, ADerived>;

protected:
    constexpr EnableStructuredBinding() = default;
    constexpr ~EnableStructuredBinding() = default;

public:
    template<gsl::index I>
    friend constexpr auto get(const ADerived& t) -> const Type<I>& { return static_cast<const EnableStructuredBinding&>(t).GetImpl<I>(); }
    template<gsl::index I>
    friend constexpr auto get(ADerived& t) -> Type<I>& { return static_cast<EnableStructuredBinding&>(t).GetImpl<I>(); }
    template<gsl::index I>
    friend constexpr auto get(ADerived&& t) -> Type<I>&& { return static_cast<EnableStructuredBinding&&>(t).GetImpl<I>(); }
    template<gsl::index I>
    friend constexpr auto get(const ADerived&& t) -> const Type<I>&& { return static_cast<const EnableStructuredBinding&&>(t).GetImpl<I>(); }

private:
    template<gsl::index I>
    constexpr auto GetImpl() const& -> const Type<I>&;
    template<gsl::index I>
    constexpr auto GetImpl() & -> Type<I>&;
    template<gsl::index I>
    constexpr auto GetImpl() && -> Type<I>&&;
    template<gsl::index I>
    constexpr auto GetImpl() const&& -> const Type<I>&&;

    constexpr auto Self() const -> const auto& { return static_cast<const ADerived&>(*this); }
    constexpr auto Self() -> auto& { return static_cast<ADerived&>(*this); }
};

template<TupleModelizable... Ts>
class Tuple final : public EnableStructuredBinding<Tuple<Ts...>> {
public:
    using Model = TupleModel<Ts...>;

private:
    struct Dummy {
        using Type = Dummy;
    };

public:
    constexpr Tuple() = default;
    constexpr explicit(sizeof...(Ts) == 1) Tuple(std::convertible_to<Ts> auto&&... values);
    constexpr explicit(sizeof...(Ts) == 1) Tuple(const typename std::conditional_t<requires { typename Ts::Type; }, Ts, Dummy>::Type&... values);
    constexpr explicit(sizeof...(Ts) == 1) Tuple(typename std::conditional_t<requires { typename Ts::Type; }, Ts, Dummy>::Type&&... values);

    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() & -> decltype(auto) { return GetImpl<Model::template Index<ANames>()...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() const& -> decltype(auto) { return GetImpl<Model::template Index<ANames>()...>(); }
    template<CETAString... ANames>
        requires(sizeof...(ANames) >= 1)
    constexpr auto Get() && -> decltype(auto) { return std::move(*this).template GetImpl<Model::template Index<ANames>()...>(); }

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
    typename TupleModel<Ts...>::StdTuple fTuple;
};

template<typename... Ts>
Tuple(Ts...) -> Tuple<Ts...>;

} // namespace MACE::Data

#include "MACE/Data/Tuple.inl"
