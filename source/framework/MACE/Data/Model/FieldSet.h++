#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/Field.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_contains.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "gsl/gsl"

#include <tuple>

namespace MACE::Data::inline Model {

namespace internal {

namespace internal {

template<typename, stdx::tuple_like, typename>
struct SignedFieldTupleHelper;

template<typename ADerived, stdx::tuple_like T, gsl::index... Is>
struct SignedFieldTupleHelper<ADerived,
                             T,
                             gslx::index_sequence<Is...>> {
    using Type = std::tuple<typename std::tuple_element_t<Is, T>::template Signed<ADerived, Is>...>;
};

template<typename ADerived, Concept::InstantiatedFrom<Field>... AFields>
struct SignedFieldTuple
    : SignedFieldTupleHelper<ADerived,
                            std::tuple<AFields...>,
                            gslx::index_sequence_for<AFields...>> {};

} // namespace internal

template<typename ADerived, Concept::InstantiatedFrom<Field>... AFields>
using SignedFieldTuple = typename internal::SignedFieldTuple<ADerived, AFields...>::Type;

} // namespace internal

template<typename ADerived, Concept::InstantiatedFrom<Field>... AFields>
class FieldSet : public NonConstructibleBase {
public:
    using FieldTuple = internal::SignedFieldTuple<ADerived, AFields...>;

    template<gsl::index I>
    using Field = std::tuple_element_t<I, FieldTuple>;

protected:
    class Entry {
    protected:
        constexpr virtual ~Entry() = 0;

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F> // should always be true
        constexpr auto Get() const -> decltype(auto) { return std::get<F>(fEntry); }

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F> // should always be true
        constexpr auto Get() -> decltype(auto) { return std::get<F>(fEntry); }

    private:
        FieldTuple fEntry;
    };
};

} // namespace MACE::Data::inline Model

#include "MACE/Data/Model/FieldSet.inl"
