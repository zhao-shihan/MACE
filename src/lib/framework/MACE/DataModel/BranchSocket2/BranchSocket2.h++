#pragma once

#include "MACE/Concept/NonMoveable.h++"
#include "MACE/Concept/ROOTFundamental.h++"

#include <concepts>
#include <type_traits>

class TTree;

namespace MACE::DataModel::inline BranchSocket {

template<class ADerived, typename T>
class BranchSocketBase2;

template<class S, typename T>
concept BranchSocket2 =
    requires(S& s, const S& cs, const T v, TTree& tree) {
        requires Concept::ROOTFundamental<T> or std::is_class_v<T>; // Fundamental type or string/array wrapper.
        { cs.Value() } -> std::same_as<const T&>;
        { s.Value(v) } -> std::same_as<void>;
        { cs.Name() } -> std::same_as<const std::string&>;
        { s.CreateBranch(tree) } -> std::same_as<void>;
        { s.ConnectToBranch(tree) } -> std::same_as<void>;
        requires not std::is_default_constructible_v<S>; // Constructor should demand the branch name, at least.
        requires Concept::NonMoveable<S>;
        requires std::derived_from<S, BranchSocketBase2<S, T>>;
        requires std::is_final_v<S>;
        requires not std::is_polymorphic_v<S>;
    };

} // namespace MACE::DataModel::inline BranchSocket
