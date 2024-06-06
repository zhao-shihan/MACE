#pragma once

#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/internal/TypeTraits.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include "TTree.h"

#include "muc/ceta_string"
#include "muc/concepts"

#include "gsl/gsl"

#include <concepts>
#include <memory>
#include <tuple>
#include <type_traits>

namespace MACE::Data::internal {

template<muc::instantiated_from<Tuple> ATuple>
class BranchHelper {
public:
    BranchHelper(ATuple& tuple);

    template<muc::ceta_string AName>
    auto CreateBranch(std::derived_from<TTree> auto& tree) -> TBranch*;
    template<muc::ceta_string AName>
    auto ConnectBranch(std::derived_from<TTree> auto& tree) -> std::pair<int, TBranch*>;
    template<muc::ceta_string AName>
    auto ConnectBranchNoCheck(std::derived_from<TTree> auto& tree) -> TBranch*;

private:
    ATuple* fTuple;
    decltype([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return std::tuple<typename std::tuple_element_t<Is, ATuple>::Type*...>{};
    }(gslx::make_index_sequence<ATuple::Size()>{})) fClassPointer;
};

} // namespace MACE::Data::internal

#include "MACE/Data/internal/BranchHelper.inl"
