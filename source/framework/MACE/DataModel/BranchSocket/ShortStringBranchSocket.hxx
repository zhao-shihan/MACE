#pragma once

#include "MACE/DataModel/BranchSocketBase.hxx"
#include "MACE/Utility/FixedString.hxx"

#include "TTree.h"

#include <string>

namespace MACE::DataModel::inline BranchSocket {

class ShortStringBranchSocket final : public BranchSocketBase<ShortStringBranchSocket, ShortString> {
public:
    ShortStringBranchSocket(const std::string& branchName, const ShortString& defaultString);

    const auto& Value() const { return fString; }
    void Value(auto&& string) { fString = std::forward<decltype(string)>(string); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName.c_str(), fString.Data(), fLeafName.c_str()); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName.c_str(), fString.Data()); }

private:
    const std::string fLeafName;
    ShortString fString;
};

} // namespace MACE::DataModel::inline BranchSocket
