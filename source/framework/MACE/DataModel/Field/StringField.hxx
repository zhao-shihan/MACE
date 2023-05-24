#pragma once

#include "MACE/DataModel/BranchSocket2/StringBranchSocket.hxx"
#include "MACE/DataModel/Field/FieldBase.hxx"
#include "MACE/Utility/FixedString.hxx"

#include <concepts>
#include <string>

namespace MACE::DataModel::inline Field {

template<class AData, gsl::index AUniqueID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
class StringField final : public FieldBase<StringField<AData, AUniqueID, AMaxSize, T>,
                                           AData, AUniqueID,
                                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                                           T> {
public:
    using Base = FieldBase<StringField<AData, AUniqueID, AMaxSize, T>,
                           AData, AUniqueID,
                           FixedString<AMaxSize>, StringBranchSocket<AMaxSize>,
                           T>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    StringField();

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fString); }

private:
    T fString;
};

template<class AData, gsl::index AUniqueID, std::convertible_to<ShortString> T>
    requires std::convertible_to<ShortString, T>
using ShortStringField = StringField<AData, AUniqueID, ShortString::MaxSize(), T>;

} // namespace MACE::DataModel::inline Field

#include "MACE/DataModel/Field/StringField.inl"
