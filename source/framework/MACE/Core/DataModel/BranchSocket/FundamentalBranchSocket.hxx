#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental ROOTFundamentalT>
class FundamentalBranchSocket final : public IBranchSocket<ROOTFundamentalT> {
public:
    FundamentalBranchSocket(const TString& branchName, ROOTFundamentalT defaultValue);
    ~FundamentalBranchSocket() noexcept = default;
    FundamentalBranchSocket(const FundamentalBranchSocket&) = delete;
    FundamentalBranchSocket& operator=(const FundamentalBranchSocket&) = delete;

    const ROOTFundamentalT& GetValue() const override { return fValue; }
    void SetValue(const ROOTFundamentalT& value) override { fValue = value; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, std::addressof(fValue)); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, std::addressof(fValue)); }

private:
    ROOTFundamentalT fValue;
};

using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.inl"
