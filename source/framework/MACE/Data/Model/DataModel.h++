#pragma once

#include "MACE/Data/Model/internal/ModelSignatureBase.h++"

#include <concepts>
#include <string_view>
#include <type_traits>

namespace MACE::Data::inline Model {

template<class M>
concept DataModel =
    requires(std::string_view sv1, std::string_view sv2) {
        requires std::derived_from<M, internal::ModelSignatureBase>;
        requires std::is_final_v<M>;
        { M::BasicName() } -> std::same_as<std::string_view>;
        requires M::BasicName().size() > 0;
        { M::Name() } -> std::same_as<std::string_view>;
        // requires M::Name() == M::BasicName();
        { M::Name(sv1) } -> std::same_as<std::string>;
        { M::Name(sv1, sv2) } -> std::same_as<std::string>;
        { M::PrefixedName(sv1) } -> std::same_as<std::string>;
        { M::SuffixedName(sv2) } -> std::same_as<std::string>;
        { M::NField() } -> std::same_as<std::size_t>;
        requires M::NField() > 0;
        { M::Topmost() } -> std::same_as<bool>;
        requires M::Topmost() != not M::Topmost();
        typename M::Entry;
    };

} // namespace MACE::DataModel
