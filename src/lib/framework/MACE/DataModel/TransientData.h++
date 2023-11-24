#pragma once

#include "MACE/Concept/NonComparable.h++"

#include <concepts>
#include <string_view>
#include <type_traits>

class TTree;

namespace MACE::DataModel {

template<typename T>
concept TransientData =
    requires(const T& data, TTree& tree) {
        requires std::semiregular<T>;
        { data.FillAllBranchSocket() } -> std::same_as<void>;
        { T::CreateAllBranch(tree) } -> std::same_as<void>;
        { T::ConnectToAllBranch(tree) } -> std::same_as<void>;
        { T::BasicTreeName() } -> std::same_as<std::string_view>;
        requires(T::BasicTreeName().length() > 0); // Name is constexpr, and not empty.
    };

} // namespace MACE::DataModel
