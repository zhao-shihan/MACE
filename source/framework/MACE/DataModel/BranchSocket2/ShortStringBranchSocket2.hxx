#pragma once

#include "MACE/DataModel/BranchSocketBase2.hxx"
#include "MACE/Utility/FixedString.hxx"

#include "TTree.h"

#include <string>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

class ShortStringBranchSocket2 final : public BranchSocketBase2<ShortStringBranchSocket2, ShortString> {
public:
    ShortStringBranchSocket2(std::string name, ShortString defaultString);

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fName.c_str(), fString.Data(), fLeafName.c_str()); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fName.c_str(), fString.Data()); }

private:
    const std::string fLeafName;
    ShortString fString;
};

} // namespace MACE::DataModel::inline BranchSocket
