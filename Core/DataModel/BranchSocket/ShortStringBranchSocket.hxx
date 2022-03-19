#pragma once

#include "ShortString.hxx"
#include "DataModel/Interface/BranchSocket.hxx"

class MACE::DataModel::ShortStringBranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<const char*, false> {
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
    ShortString   fString;
};
