#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"

#include <concepts>
#include <type_traits>

class TTree;

namespace MACE::Core::DataModel {

template<class ADerived, typename T>
class BranchSocketBase;

template<class S, typename T>
concept BranchSocketable = requires(S& s, const S& cs, const T v, TTree& tree) {
    requires Concept::ROOTFundamental<T> or std::is_class_v<T>; // Fundamental type or string/array wrapper.
    requires requires {
        { cs.Value() } -> std::same_as<T>;
    } or requires {
        { cs.Value() } -> std::same_as<const T&>;
    };
    { s.Value(v) } -> std::same_as<void>;
    { s.CreateBranch(tree) } -> std::same_as<void>;
    { s.ConnectToBranch(tree) } -> std::same_as<void>;
    requires std::derived_from<S, BranchSocketBase<S, T>>;
    requires std::is_final_v<S>;
    requires not std::is_default_constructible_v<S>; // Constructor should need the branch name, at least.
};

} // namespace MACE::Core::DataModel
