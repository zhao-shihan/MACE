#pragma once

#include "MACE/DataModel/BranchSocketBase.h++"
#include "MACE/Utility/FixedString.h++"

#include "TTree.h"

#include <string>

namespace MACE::DataModel::inline BranchSocket {

class ShortStringBranchSocket final : public BranchSocketBase<ShortStringBranchSocket, String15> {
public:
    ShortStringBranchSocket(const std::string& branchName, const String15& defaultString);

    const auto& Value() const { return fString; }
    void Value(auto&& string) { fString = std::forward<decltype(string)>(string); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName.c_str(), fString.Data(), fLeafName.c_str()); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName.c_str(), fString.Data()); }

private:
    const std::string fLeafName;
    String15 fString;
};

} // namespace MACE::DataModel::inline BranchSocket
