#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/Data/Entry.h++"
#include "MACE/Data/internal/TypeTraits.h++"

#include "gsl/gsl"

#include <memory>
#include <type_traits>
#include <unordered_map>

namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Entry> AEntry>
class BranchAddressHelper {
public:
    template<gsl::index I>
    auto FieldPointer(AEntry& entry);

private:
    std::unordered_map<gsl::index, void*> fClassPointer;
};

} // namespace MACE::Data::internal

#include "MACE/Data/internal/BranchAddressHelper.inl"
