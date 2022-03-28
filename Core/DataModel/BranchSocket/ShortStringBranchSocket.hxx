#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "Utility/ShortString.hxx"

namespace MACE::Core::DataModel::BranchSocket {

using Utility::ShortString;

class ShortStringBranchSocket final : public IBranchSocket<const char*, false> {
public:
    ShortStringBranchSocket(const char* branchName, const char* defaultString);
    ~ShortStringBranchSocket() noexcept = default;
    ShortStringBranchSocket(const ShortStringBranchSocket&) = delete;
    ShortStringBranchSocket& operator=(const ShortStringBranchSocket&) = delete;

    [[nodiscard]] const char* GetValue() const override { return fString; }
    void SetValue(const char* string) override { fString = string; }

    void CreateBranch(TTree& tree) override { tree.Branch(fBranchName, fString, fBranchNameWithType); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(fBranchName, fString); }

private:
    const TString fBranchName;
    const TString fBranchNameWithType;
    ShortString fString;
};

} // namespace MACE::Core::DataModel::BranchSocket
