#pragma once

#include "DataModel/Interface/BranchSocket.hxx"

template<MACE::DataModel::FundamentalType Fund_t>
class MACE::DataModel::FundamentalBranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<Fund_t> {
public:
    FundamentalBranchSocket(const char* branchName, Fund_t defaultValue);
    ~FundamentalBranchSocket() noexcept = default;
    FundamentalBranchSocket(const FundamentalBranchSocket&) = delete;
    FundamentalBranchSocket& operator=(const FundamentalBranchSocket&) = delete;

    [[nodiscard]] const Fund_t& GetValue() const override { return fValue; }
    void SetValue(const Fund_t& value) override { fValue = value; }

    void CreateBranch(TTree& tree) override { tree.Branch(fBranchName, std::addressof(fValue)); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(fBranchName, std::addressof(fValue)); }

private:
    const TString fBranchName;
    Fund_t        fValue;
};

#include "DataModel/BranchSocket/FundamentalBranchSocket.ixx"

namespace MACE::DataModel::inline BranchSocket{
    using IntBranchSocket = FundamentalBranchSocket<Int_t>;
    using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
    using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;
}
