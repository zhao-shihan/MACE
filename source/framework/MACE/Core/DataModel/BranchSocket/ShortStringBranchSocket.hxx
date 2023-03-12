#pragma once

#include "MACE/Core/DataModel/BranchSocketBase.hxx"
#include "MACE/Utility/FixedString.hxx"

#include <string>

namespace MACE::Core::DataModel::BranchSocket {

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

} // namespace MACE::Core::DataModel::BranchSocket
