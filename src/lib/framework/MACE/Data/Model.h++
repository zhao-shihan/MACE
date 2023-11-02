#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/CEvalNTSTA.h++"
#include "MACE/Data/Field.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_concat.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "gsl/gsl"

#include <concepts>
#include <string_view>
#include <tuple>

namespace MACE::Data {

namespace internal {

struct ModelSignature : NonConstructibleBase {};

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> AFieldTuple>
struct ModelBase : ModelSignature {
    using FieldTuple = AFieldTuple;
    template<gsl::index I>
    using Field = std::tuple_element_t<I, FieldTuple>;

    static constexpr auto NField() { return std::tuple_size_v<FieldTuple>; }

    static constexpr auto Name();
    template<gsl::index I>
        requires(0 <= I and I < NField())
    static constexpr auto Name() -> const auto& { return std::get<I>(Name()); }

    static constexpr auto Title();
    template<gsl::index I>
        requires(0 <= I and I < NField())
    static constexpr auto Title() -> const auto& { return std::get<I>(Title()); }

    template<CEvalNTSTA AName>
    static constexpr auto Index() { return IndexImpl<AName>(); }

private:
    template<CEvalNTSTA AName, gsl::index I = NField() - 1>
    static constexpr auto IndexImpl();
};

template<typename T>
concept IsModel = std::derived_from<T, ModelSignature>;

namespace internal {

template<typename>
struct IsField
    : std::false_type {};
template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle>
struct IsField<Field<T, AName, ATitle>>
    : std::true_type {};

} // namespace internal

template<typename T>
concept IsField = internal::IsField<T>::value;

} // namespace internal

template<typename T>
concept Modelizable = static_cast<bool>(internal::IsModel<T> xor internal::IsField<T>);

template<Modelizable... Ts>
struct Model; // fields should be placed after data models in template parameters!

template<internal::IsModel AModel, Modelizable... AOthers>
struct Model<AModel, AOthers...> final
    : internal::ModelBase<Model<AModel, AOthers...>,
                          stdx::tuple_concat_t<typename AModel::FieldTuple,
                                               typename Model<AOthers...>::FieldTuple>> {};

template<GoodFieldValueType... Ts, CEvalNTSTA... ANames, CEvalNTSTA... ATitles>
struct Model<Field<Ts, ANames, ATitles>...> final
    : internal::ModelBase<Model<Field<Ts, ANames, ATitles>...>,
                          std::tuple<Field<Ts, ANames, ATitles>...>> {};

template<>
struct Model<> final
    : internal::ModelBase<Model<>,
                          std::tuple<>> {};

} // namespace MACE::Data

#include "MACE/Data/Model.inl"
