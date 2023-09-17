#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/ModelSegment.h++"

#include "fmt/format.h"

#include <concepts>
#include <string_view>
#include <tuple>

namespace MACE::Data::inline Model {

template<typename ADerived,
         Concept::InstantiatedFrom<std::tuple> ABaseFieldSetTuple,
         Concept::InstantiatedFrom<std::tuple> AThisFieldSetTuple>
class Modelize : public ModelSegment<ADerived,
                                     ABaseFieldSetTuple,
                                     AThisFieldSetTuple> {
public:
    static constexpr auto Name() -> std::string_view;
    static auto Name(const auto& prefix) -> std::string { return fmt::format("{}{}", prefix, Name()); }
    static auto Name(const auto& prefix, const auto& suffix) -> std::string { return fmt::format("{}{}{}", prefix, Name(), suffix); }
    static auto PrefixedName(const auto& prefix) -> std::string { return fmt::format("{}{}", prefix, Name()); }
    static auto SuffixedName(const auto& suffix) -> std::string { return fmt::format("{}{}", Name(), suffix); }
};

} // namespace MACE::Data::inline Model

#include "MACE/Data/Model/Modelize.inl"
