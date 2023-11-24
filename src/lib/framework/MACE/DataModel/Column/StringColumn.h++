#pragma once

#include "MACE/DataModel/BranchSocket2/StringBranchSocket.h++"
#include "MACE/DataModel/Column/ColumnBase.h++"
#include "MACE/Utility/FixedString.h++"

#include <concepts>
#include <string>

namespace MACE::DataModel::inline Column {

template<typename AData, gsl::index AUniqueID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
class StringColumn final : public ColumnBase<StringColumn<AData, AUniqueID, AMaxSize, T>,
                                           AData, AUniqueID,
                                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                                           T> {
public:
    using Base = ColumnBase<StringColumn<AData, AUniqueID, AMaxSize, T>,
                           AData, AUniqueID,
                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                           T>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    StringColumn();

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fString); }

private:
    T fString;
};

template<typename AData, gsl::index AUniqueID, std::convertible_to<ShortString> T>
    requires std::convertible_to<ShortString, T>
using ShortStringColumn = StringColumn<AData, AUniqueID, ShortString::MaxSize(), T>;

} // namespace MACE::DataModel::inline Column

#include "MACE/DataModel/Column/StringColumn.inl"
