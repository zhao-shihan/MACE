#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "IsROOTFundamental.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
class FundamentalBranchSocket final : public IBranchSocket<Fund_t> {
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
    Fund_t fValue;
};

using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.ixx"
