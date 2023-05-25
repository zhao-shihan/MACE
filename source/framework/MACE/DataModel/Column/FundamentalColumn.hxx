#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"
#include "MACE/DataModel/BranchSocket2/FundamentalBranchSocket2.hxx"
#include "MACE/DataModel/Column/ColumnBase.hxx"

#include "RtypesCore.h"

#include <concepts>
#include <string>
#include <utility>

namespace MACE::DataModel::inline Column {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, typename U>
    requires(std::integral<T> and std::integral<U>) or
            (std::floating_point<T> and std::floating_point<U>)
class FundamentalColumn final : public ColumnBase<FundamentalColumn<AData, AUniqueID, T, U>,
                                                AData, AUniqueID,
                                                T, FundamentalBranchSocket2<T>,
                                                U> {
public:
    using Base = ColumnBase<FundamentalColumn<AData, AUniqueID, T, U>,
                           AData, AUniqueID,
                           T, FundamentalBranchSocket2<T>,
                           U>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    FundamentalColumn();

    const auto& Value() const { return fValue; }
    void Value(auto&& v) { fValue = std::forward<decltype(v)>(v); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fValue); }

private:
    U fValue;
};

#define MACE_DATA_MODEL_ENTRY_FUNDAMENTAL_ENTRY_ALIAS(Type)                    \
    template<class AData, gsl::index AUniqueID, typename T>                  \
        requires(std::integral<Type##_t> and std::integral<T>) or              \
                    (std::floating_point<Type##_t> and std::floating_point<T>) \
    using Type##Column = FundamentalColumn<AData, AUniqueID, Type##_t, T>;

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

} // namespace MACE::DataModel::inline Column

#include "MACE/DataModel/Column/FundamentalColumn.inl"
