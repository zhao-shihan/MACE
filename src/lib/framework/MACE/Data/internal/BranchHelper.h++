#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/internal/TypeTraits.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/CETAString.h++"

#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <memory>
#include <tuple>
#include <type_traits>

namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Tuple> ATuple>
class BranchHelper {
public:
    BranchHelper(ATuple& tuple);

    template<CETAString AName>
    auto CreateBranch(std::derived_from<TTree> auto& tree) -> TBranch*;
    template<CETAString AName>
    auto ConnectBranch(std::derived_from<TTree> auto& tree) -> std::pair<int, TBranch*>;
    template<CETAString AName>
    auto ConnectBranchNoCheck(std::derived_from<TTree> auto& tree) -> TBranch*;

private:
    ATuple* fTuple;
    decltype([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return std::tuple<typename std::tuple_element_t<Is, ATuple>::Type*...>{};
    }(gslx::make_index_sequence<ATuple::Size()>{})) fClassPointer;
};

} // namespace MACE::Data::internal

#include "MACE/Data/internal/BranchHelper.inl"
