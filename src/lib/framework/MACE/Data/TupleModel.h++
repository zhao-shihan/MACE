#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_concat.h++"
#include "MACE/Utility/CETAString.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "gsl/gsl"

#include <algorithm>
#include <array>
#include <concepts>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace MACE::Data {

namespace internal {

struct ModelSignature : NonConstructibleBase {};

namespace internal {

template<typename T>
concept UniqueStdTuple =
    requires {
        requires Concept::InstantiatedFrom<T, std::tuple>;
        requires(
            []<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return (... and
                        ([]<gsl::index... Js, gsl::index I>(gslx::index_sequence<Js...>, std::integral_constant<gsl::index, I>) {
                            return (... and
                                    (I != Js or std::tuple_element_t<I, T>::Name() == std::tuple_element_t<Js, T>::Name()));
                        }(gslx::make_index_sequence<std::tuple_size_v<T>>{}, std::integral_constant<gsl::index, Is>{})));
            }(gslx::make_index_sequence<std::tuple_size_v<T>>{}));
    };

} // namespace internal

template<typename ADerived, internal::UniqueStdTuple AStdTuple>
struct ModelBase : ModelSignature {
    using StdTuple = AStdTuple;

    static constexpr auto Size() { return std::tuple_size_v<StdTuple>; }

    template<CETAString AName>
    static constexpr auto Index() { return IndexImpl<AName>(); }

    template<CETAString AName>
    using ValueOf = std::tuple_element_t<Index<AName>(), StdTuple>;

private:
    template<CETAString AName, gsl::index I = 0>
    static consteval auto IndexImpl() -> gsl::index;
};

} // namespace internal

template<typename T>
concept TupleModelizable = static_cast<bool>(std::derived_from<T, internal::ModelSignature> xor internal::IsValue<T>::value);

template<TupleModelizable...>
struct TupleModel final
    : internal::ModelBase<TupleModel<>,
                          std::tuple<>> {};

template<std::derived_from<internal::ModelSignature> AModel, TupleModelizable... AOthers>
struct TupleModel<AModel, AOthers...> final
    : internal::ModelBase<TupleModel<AModel, AOthers...>,
                          stdx::tuple_concat_t<typename AModel::StdTuple,
                                               typename TupleModel<AOthers...>::StdTuple>> {};

template<ValueAcceptable T, CETAString AName, CETAString ADescription, TupleModelizable... AOthers>
struct TupleModel<Value<T, AName, ADescription>, AOthers...> final
    : internal::ModelBase<TupleModel<Value<T, AName, ADescription>, AOthers...>,
                          stdx::tuple_concat_t<std::tuple<Value<T, AName, ADescription>>,
                                               typename TupleModel<AOthers...>::StdTuple>> {};

template<typename M1, typename M2>
concept TupleModelContain = requires {
    requires Concept::InstantiatedFrom<M1, TupleModel>;
    requires Concept::InstantiatedFrom<M2, TupleModel>;
    requires M1::Size() >= M2::Size();
    requires(
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and
                    ([]<gsl::index... Js, gsl::index I>(gslx::index_sequence<Js...>, std::integral_constant<gsl::index, I>) {
                        return (... or
                                (std::tuple_element_t<Js, typename M1::StdTuple>::Name() ==
                                 std::tuple_element_t<I, typename M2::StdTuple>::Name()));
                    }(gslx::make_index_sequence<M1::Size()>{}, std::integral_constant<gsl::index, Is>{})));
        }(gslx::make_index_sequence<M2::Size()>{}));
};

template<typename M1, typename M2>
concept TupleModelEquivalent = requires {
    requires TupleModelContain<M1, M2>;
    requires TupleModelContain<M2, M1>;
};

} // namespace MACE::Data

#include "MACE/Data/TupleModel.inl"
