#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"
#include "MACE/DataModel/BranchSocket2/FundamentalBranchSocket2.hxx"
#include "MACE/DataModel/EntryBase.hxx"

#include <concepts>
#include <string>

namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index BranchIndex, Concept::ROOTFundamental T, typename U>
    requires std::convertible_to<const T&, U> and std::assignable_from<T&, const U&>
class FundamentalEntry final : public EntryBase<FundamentalEntry<AData, BranchIndex, T, U>,
                                                AData, BranchIndex,
                                                T, FundamentalBranchSocket2<T>,
                                                U> {
public:
    using Base = EntryBase<FundamentalEntry<AData, BranchIndex, T, U>,
                           AData, BranchIndex,
                           T, FundamentalBranchSocket2<T>,
                           U>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    FundamentalEntry();
};

#define MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Type)                                            \
    template<class AData, gsl::index BranchIndex, typename T>                                          \
        requires std::convertible_to<const Type##_t&, T> and std::assignable_from<Type##_t&, const T&> \
    using Type##Entry = FundamentalEntry<AData, BranchIndex, Type##_t, T>;

MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Char)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(UChar)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Short)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(UShort)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Int)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(UInt)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Float)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Double)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Long64)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(ULong64)
MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Bool)

#undef MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS

} // namespace MACE::DataModel::inline Entry

#include "MACE/DataModel/Entry/FundamentalEntry.inl"
