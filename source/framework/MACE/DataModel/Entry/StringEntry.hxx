#pragma once

#include "MACE/DataModel/BranchSocket2/StringBranchSocket.hxx"
#include "MACE/DataModel/EntryBase.hxx"
#include "MACE/Utility/FixedString.hxx"

#include <concepts>
#include <string>

namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index ABranchID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
class StringEntry final : public EntryBase<StringEntry<AData, ABranchID, AMaxSize, T>,
                                           AData, ABranchID,
                                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                                           T> {
public:
    using Base = EntryBase<StringEntry<AData, ABranchID, AMaxSize, T>,
                           AData, ABranchID,
                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                           T>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    StringEntry();

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fString); }

private:
    T fString;
};

template<class AData, gsl::index ABranchID, std::convertible_to<ShortString> T>
    requires std::convertible_to<ShortString, T>
using ShortStringEntry = StringEntry<AData, ABranchID, ShortString::MaxSize(), T>;

} // namespace MACE::DataModel::inline Entry

#include "MACE/DataModel/Entry/StringEntry.inl"
