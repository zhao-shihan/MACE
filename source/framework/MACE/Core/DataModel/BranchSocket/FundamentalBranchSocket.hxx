#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental AROOTFundamental>
class FundamentalBranchSocket final : public IBranchSocket<AROOTFundamental> {
public:
    FundamentalBranchSocket(const TString& branchName, AROOTFundamental defaultValue);
    ~FundamentalBranchSocket() noexcept = default;
    FundamentalBranchSocket(const FundamentalBranchSocket&) = delete;
    FundamentalBranchSocket& operator=(const FundamentalBranchSocket&) = delete;

    const AROOTFundamental& GetValue() const override { return fValue; }
    void SetValue(const AROOTFundamental& value) override { fValue = value; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, &fValue); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, &fValue); }

private:
    AROOTFundamental fValue;
};

using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.inl"
