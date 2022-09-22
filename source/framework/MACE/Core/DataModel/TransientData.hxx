#pragma once

#include "MACE/Concept/NonComparable.hxx"

#include <concepts>
#include <string_view>
#include <type_traits>

class TTree;

namespace MACE::Core::DataModel {

template<class T>
concept TransientData = requires(const T& data, TTree& tree) {
    requires std::semiregular<T>;
    requires std::is_nothrow_default_constructible_v<T>;
    requires std::is_nothrow_copy_constructible_v<T>;
    requires std::is_nothrow_copy_assignable_v<T>;
    requires std::is_nothrow_move_constructible_v<T>;
    requires std::is_nothrow_move_assignable_v<T>; // clang-format off
    { data.FillBranchSockets() } noexcept -> std::same_as<void>; // clang-format on
    { T::CreateBranches(tree) } -> std::same_as<void>;
    { T::ConnectToBranches(tree) } -> std::same_as<void>;
    { T::BasicTreeName() } -> std::same_as<std::string_view>;
    requires(T::BasicTreeName().length() > 0); // Name is constexpr, and not empty.
};

} // namespace MACE::Core::DataModel
