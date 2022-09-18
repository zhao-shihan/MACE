#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"

namespace MACE::Core::DataModel::BranchSocket {

template<ROOTFundamental T>
class FundamentalBranchSocket final : public IBranchSocket<T> {
public:
    FundamentalBranchSocket(const TString& branchName, T defaultValue);

    const T& Value() const override { return fValue; }
    void Value(const T& value) override { fValue = value; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, &fValue); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, &fValue); }

private:
    T fValue;
};

using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.inl"
