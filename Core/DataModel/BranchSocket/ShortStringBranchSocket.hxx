#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "Utility/ShortString.hxx"

namespace MACE::Core::DataModel::BranchSocket {

using Utility::ShortString;

class ShortStringBranchSocket final : public IBranchSocket<ShortString> {
public:
    ShortStringBranchSocket(const TString& branchName, const ShortString& defaultString);
    ~ShortStringBranchSocket() noexcept = default;
    ShortStringBranchSocket(const ShortStringBranchSocket&) = delete;
    ShortStringBranchSocket& operator=(const ShortStringBranchSocket&) = delete;

    const ShortString& GetValue() const override { return fString; }
    void SetValue(const ShortString& string) override { fString = string; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fString, fLeafName); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fString); }

private:
    const TString fLeafName;
    ShortString fString;
};

} // namespace MACE::Core::DataModel::BranchSocket
