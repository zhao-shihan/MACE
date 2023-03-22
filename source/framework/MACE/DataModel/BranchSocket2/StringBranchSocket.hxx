#pragma once

#include "MACE/DataModel/BranchSocketBase2.hxx"
#include "MACE/Utility/FixedString.hxx"

#include "TTree.h"

#include <string>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

template<std::size_t AMaxSize>
class StringBranchSocket final : public BranchSocketBase2<StringBranchSocket<AMaxSize>, FixedString<AMaxSize>> {
public:
    StringBranchSocket(std::string name, FixedString<AMaxSize> defaultString);

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fName.c_str(), fString.Data(), fLeafName.c_str()); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fName.c_str(), fString.Data()); }

    static constexpr auto MaxSize() { return AMaxSize; }

private:
    const std::string fLeafName;
    FixedString<AMaxSize> fString;
};

using ShortStringBranchSocket2 = StringBranchSocket<15>;

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/StringBranchSocket.inl"
