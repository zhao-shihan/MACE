#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/DataModel.h++"
#include "MACE/Data/Model/Field/NamedField.h++"
#include "MACE/Data/Model/FieldSet.h++"
#include "MACE/Data/Model/internal/ModelSignatureBase.h++"
#include "MACE/Extension/stdx/tuple_concat.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <concepts>
#include <string_view>
#include <tuple>
#include <utility>

namespace MACE::Data::inline Model {

using namespace std::string_view_literals;

template<class ADerived,
         stdx::tuple_like ABaseFieldSetTuple,
         stdx::tuple_like AThisFieldSetTuple>
class ModelBase;

namespace internal {

template<stdx::tuple_like FieldTuple>
class BasicFieldSetWithTuple;

template<NamedField... AFields>
class BasicFieldSetWithTuple<std::tuple<AFields...>>
    : public FieldSet<BasicField<typename AFields::Type>...> {};

template<Concept::InstantiatedFrom<FieldSet>... FieldSets>
class BasicFieldSetHelper
    : public BasicFieldSetWithTuple<stdx::tuple_concat_t<typename FieldSets::FieldTuple...>> {};

} // namespace internal

enum class FieldIndexMode {
    Absolute,
    Relative
};

template<class ADerived,
         Concept::InstantiatedFrom<FieldSet>... ABaseFieldSets,
         Concept::InstantiatedFrom<FieldSet>... ANewFieldSets>
class ModelBase<ADerived,
                std::tuple<ABaseFieldSets...>,
                std::tuple<ANewFieldSets...>> : public internal::ModelSignatureBase,
                                                public internal::BasicFieldSetHelper<ABaseFieldSets...,
                                                                                     ANewFieldSets...> {
private:
    using BaseFieldTuple = stdx::tuple_concat_t<typename ABaseFieldSets::FieldTuple...>;

public:
    using FieldTuple = stdx::tuple_concat_t<BaseFieldTuple, typename ANewFieldSets::FieldTuple...>;

    template<gsl::index I, FieldIndexMode IM = FieldIndexMode::Absolute>
    using Field = std::tuple_element_t<IM == FieldIndexMode::Absolute ?
                                           I :
                                           I + std::tuple_size_v<BaseFieldTuple>,
                                       FieldTuple>;

public:
    static constexpr auto Name() -> std::string_view;
    static auto Name(const auto& prefix) -> std::string { return fmt::format("{}{}"sv, prefix, Name()); }
    static auto Name(const auto& prefix, const auto& suffix) -> std::string { return fmt::format("{}{}{}"sv, prefix, Name(), suffix); }
    static auto PrefixedName(const auto& prefix) -> std::string { return fmt::format("{}{}"sv, prefix, Name()); }
    static auto SuffixedName(const auto& suffix) -> std::string { return fmt::format("{}{}"sv, Name(), suffix); }

    static constexpr auto NField() { return std::tuple_size_v<FieldTuple>; }
    static constexpr auto Topmost() { return std::tuple_size_v<BaseFieldTuple> == 0; }

public:
    class Entry : public ABaseFieldSets::Entry...,
                  public ANewFieldSets::Entry... {
    protected:
        constexpr Entry() = default;
        constexpr virtual ~Entry() override = 0;

    public:
        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F>
        constexpr auto Get() const -> decltype(auto) { return this->template The<F>(); }
        template<gsl::index I, FieldIndexMode IM = FieldIndexMode::Absolute>
        constexpr auto Get() const -> decltype(auto) { return Get<Field<I, IM>>(); }

        template<typename F>
            requires stdx::tuple_contains_unique_v<FieldTuple, F>
        constexpr auto Get() -> decltype(auto) { return this->template The<F>(); }
        template<gsl::index I, FieldIndexMode IM = FieldIndexMode::Absolute>
        constexpr auto Get() -> decltype(auto) { return Get<Field<I, IM>>(); }
    };
};

} // namespace MACE::Data::inline Model

#include "MACE/Data/Model/ModelBase.inl"
