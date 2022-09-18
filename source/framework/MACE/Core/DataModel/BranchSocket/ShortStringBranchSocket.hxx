#pragma once

#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"
#include "MACE/Utility/FixedString.hxx"

namespace MACE::Core::DataModel::BranchSocket {

using Utility::ShortString;

class ShortStringBranchSocket final : public IBranchSocket<ShortString> {
public:
    ShortStringBranchSocket(const TString& branchName, const ShortString& defaultString);

    const ShortString& Value() const override { return fString; }
    void Value(const ShortString& string) override { fString = string; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fString.Data(), fLeafName); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fString.Data()); }

private:
    const TString fLeafName;
    ShortString fString;
};

} // namespace MACE::Core::DataModel::BranchSocket
