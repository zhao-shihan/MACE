#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/FieldSetLike.h++"
#include "MACE/Extension/stdx/tuple_concat.h++"

#include "gsl/gsl"

#include <concepts>
#include <tuple>
#include <utility>

namespace MACE::Data::inline Model {

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> ABaseFieldSetTuple,
         Concept::InstantiatedFrom<std::tuple> AThisFieldSetTuple>
    requires(
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and FieldSetLike<std::tuple_element_t<Is, ABaseFieldSetTuple>>);
        }(gslx::make_index_sequence<std::tuple_size_v<ABaseFieldSetTuple>>{}) and
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and FieldSetLike<std::tuple_element_t<Is, AThisFieldSetTuple>>);
        }(gslx::make_index_sequence<std::tuple_size_v<AThisFieldSetTuple>>{}))
class ModelSegment;

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
class ModelSegment<ADerived,
                   std::tuple<ABaseFieldSets...>,
                   std::tuple<ANewFieldSets...>> : public ABaseFieldSets...,
                                                   public ANewFieldSets... {
private:
    using BaseFieldTuple = stdx::tuple_concat_t<typename ABaseFieldSets::FieldTuple...>;

public:
    using FieldTuple = stdx::tuple_concat_t<BaseFieldTuple, typename ANewFieldSets::FieldTuple...>;
    template<gsl::index I>
    using Field = std::tuple_element_t<I, FieldTuple>;

protected:
    template<gsl::index I>
    using LocalField = Field<I + std::tuple_size_v<BaseFieldTuple>>;

public:
    static constexpr auto NField() { return std::tuple_size_v<FieldTuple>; }
    static constexpr auto Topmost() { return std::tuple_size_v<BaseFieldTuple> == 0; }

public:
    class Entry : public ABaseFieldSets::Entry...,
                  public ANewFieldSets::Entry... {
    public:
        using Model = ADerived;

    protected:
        constexpr virtual ~Entry() override = 0;

    public:
        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F> // should always be true
        constexpr auto Get() const -> decltype(auto) { return GetImpl<F>(); }
        template<gsl::index I>
        constexpr auto Get() const -> decltype(auto) { return Get<Field<I>>(); }

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F> // should always be true
        constexpr auto Get() -> decltype(auto) { return GetImpl<F>(); }
        template<gsl::index I>
        constexpr auto Get() -> decltype(auto) { return Get<Field<I>>(); }

        static constexpr auto NField() { return Model::NField(); }

    protected:
        template<gsl::index I>
        constexpr auto GetLocal() const -> decltype(auto) { return Get<LocalField<I>>(); }
        template<gsl::index I>
        constexpr auto GetLocal() -> decltype(auto) { return Get<LocalField<I>>(); }

    private:
        template<typename F, gsl::index IFieldSet = 0>
        constexpr auto GetImpl() const -> decltype(auto);
        template<typename F, gsl::index IFieldSet = 0>
        constexpr auto GetImpl() -> decltype(auto);
    };
};

} // namespace MACE::Data::inline Model

#include "MACE/Data/Model/ModelSegment.inl"
