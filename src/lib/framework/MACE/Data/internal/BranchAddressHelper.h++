#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/Utility/CETAString.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/internal/TypeTraits.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include "gsl/gsl"

#include <memory>
#include <tuple>
#include <type_traits>

namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Tuple> ATuple>
class BranchAddressHelper {
public:
    template<CETAString AName>
    auto ValuePointer(ATuple& entry) -> auto;

private:
    decltype([]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return std::tuple<typename std::tuple_element_t<Is, ATuple>::Type*...>{};
    }(gslx::make_index_sequence<ATuple::Size()>{})) fClassPointer;
};

} // namespace MACE::Data::internal

#include "MACE/Data/internal/BranchAddressHelper.inl"
