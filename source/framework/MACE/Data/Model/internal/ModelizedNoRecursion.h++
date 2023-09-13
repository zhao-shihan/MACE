#pragma once

#include "MACE/Data/Model/FieldSetLike.h++"

#include <concepts>
#include <string_view>

namespace MACE::Data::inline Model::internal {

template<class M>
concept ModelizedNoRecursion =
    requires(std::string_view sv1, std::string_view sv2) {
        requires FieldSetLike<M>;
        { M::BasicName() } -> std::same_as<std::string_view>;
        requires not M::BasicName().empty();
        { M::Name() } -> std::same_as<std::string_view>;
        requires M::Name() == M::BasicName();
        { M::Name(sv1) } -> std::same_as<std::string>;
        { M::Name(sv1, sv2) } -> std::same_as<std::string>;
        { M::PrefixedName(sv1) } -> std::same_as<std::string>;
        { M::SuffixedName(sv2) } -> std::same_as<std::string>;
        { M::NField() } -> std::same_as<std::size_t>;
        requires M::NField() > 0;
        { M::Topmost() } -> std::same_as<bool>;
        requires M::Topmost() == true or M::Topmost() == false;
        typename M::Entry;
        typename M::Entry::Model;
        requires std::same_as<M, typename M::Entry::Model>;
    };

} // namespace MACE::Data::inline Model
