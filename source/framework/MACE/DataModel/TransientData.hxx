#pragma once

#include "MACE/Concept/NonComparable.hxx"

#include <concepts>
#include <string_view>
#include <type_traits>

class TTree;

namespace MACE::DataModel {

template<class T>
concept TransientData =
    requires(const T& data, TTree& tree) {
        requires std::semiregular<T>;
        { data.FillBranchSockets() } -> std::same_as<void>;
        { T::CreateBranches(tree) } -> std::same_as<void>;
        { T::ConnectToBranches(tree) } -> std::same_as<void>;
        { T::BasicTreeName() } -> std::same_as<std::string_view>;
        requires(T::BasicTreeName().length() > 0); // Name is constexpr, and not empty.
    };

} // namespace MACE::DataModel
