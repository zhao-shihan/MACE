#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/Field/BasicField.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_contains.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "gsl/gsl"

#include <tuple>

namespace MACE::Data::inline Model {

namespace internal {

namespace internal {

template<typename, stdx::tuple_like, typename>
struct MakeNamedFieldTupleHelper;

template<typename AFieldSet, stdx::tuple_like T, gsl::index... Is>
struct MakeNamedFieldTupleHelper<AFieldSet,
                                 T,
                                 gslx::index_sequence<Is...>> {
    using Type = std::tuple<typename std::tuple_element_t<Is, T>::template Named<AFieldSet, Is>...>;
};

template<typename AFieldSet, Concept::InstantiatedFrom<BasicField>... AFields>
struct MakeNamedFieldTuple
    : MakeNamedFieldTupleHelper<AFieldSet,
                                std::tuple<AFields...>,
                                gslx::index_sequence_for<AFields...>> {};

} // namespace internal

template<typename AFieldSet, Concept::InstantiatedFrom<BasicField>... AFields>
using MakeNamedFieldTuple = typename internal::MakeNamedFieldTuple<AFieldSet, AFields...>::Type;

} // namespace internal

template<typename AFieldSet, Concept::InstantiatedFrom<BasicField>... AFields>
class FieldSet : public NonConstructibleBase {
public:
    using FieldTuple = internal::MakeNamedFieldTuple<AFieldSet, AFields...>;

    template<gsl::index I>
    using Field = std::tuple_element_t<I, FieldTuple>;

    class Entry {
    protected:
        constexpr Entry() = default;
        constexpr virtual ~Entry() = 0;

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F>
        constexpr auto The() const -> decltype(auto) { return std::get<F>(fEntry); }

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F>
        constexpr auto The() -> decltype(auto) { return std::get<F>(fEntry); }

    private:
        FieldTuple fEntry;
    };
};

} // namespace MACE::Data::inline Model

#include "MACE/Data/Model/FieldSet.inl"
