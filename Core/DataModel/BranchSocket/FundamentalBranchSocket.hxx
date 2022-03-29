#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
class FundamentalBranchSocket final : public IBranchSocket<Fund_t> {
public:
    FundamentalBranchSocket(const TString& branchName, Fund_t defaultValue);
    ~FundamentalBranchSocket() noexcept = default;
    FundamentalBranchSocket(const FundamentalBranchSocket&) = delete;
    FundamentalBranchSocket& operator=(const FundamentalBranchSocket&) = delete;

    const Fund_t& GetValue() const override { return fValue; }
    void SetValue(const Fund_t& value) override { fValue = value; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, std::addressof(fValue)); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, std::addressof(fValue)); }

private:
    Fund_t fValue;
};

using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.ixx"
