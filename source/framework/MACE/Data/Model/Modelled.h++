#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/DataModel.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/FieldSetLike.h++"
#include "MACE/Data/Model/NamedField.h++"
#include "MACE/Extension/stdx/tuple_concat.h++"
#include "MACE/Utility/NonConstructibleBase.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <concepts>
#include <string_view>
#include <tuple>
#include <utility>

namespace MACE::Data::inline Model {

template<typename ADerived,
         stdx::tuple_like ABaseFieldSetTuple,
         stdx::tuple_like AThisFieldSetTuple>
class Modelled;

template<typename ADerived,
         FieldSetLike... ABaseFieldSets,
         FieldSetLike... ANewFieldSets>
class Modelled<ADerived,
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
    static constexpr auto Name() -> std::string_view;
    static auto Name(const auto& prefix) -> std::string { return fmt::format("{}{}", prefix, Name()); }
    static auto Name(const auto& prefix, const auto& suffix) -> std::string { return fmt::format("{}{}{}", prefix, Name(), suffix); }
    static auto PrefixedName(const auto& prefix) -> std::string { return fmt::format("{}{}", prefix, Name()); }
    static auto SuffixedName(const auto& suffix) -> std::string { return fmt::format("{}{}", Name(), suffix); }

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

#include "MACE/Data/Model/Modelled.inl"
