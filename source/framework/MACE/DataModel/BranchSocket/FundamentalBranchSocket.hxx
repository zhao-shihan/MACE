#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"
#include "MACE/DataModel/BranchSocketBase.hxx"

#include <string>

namespace MACE::DataModel::BranchSocket {

template<Concept::ROOTFundamental T>
class FundamentalBranchSocket final : public BranchSocketBase<FundamentalBranchSocket<T>, T> {
public:
    FundamentalBranchSocket(const std::string& branchName, T defaultValue);

    const T& Value() const { return fValue; }
    void Value(const T& value) { fValue = value; }

    void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName.c_str(), &fValue); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName.c_str(), &fValue); }

private:
    T fValue;
};

using CharBranchSocket = FundamentalBranchSocket<Char_t>;
using UCharBranchSocket = FundamentalBranchSocket<UChar_t>;
using ShortBranchSocket = FundamentalBranchSocket<Short_t>;
using UShortBranchSocket = FundamentalBranchSocket<UShort_t>;
using IntBranchSocket = FundamentalBranchSocket<Int_t>;
using UIntBranchSocket = FundamentalBranchSocket<UInt_t>;
using FloatBranchSocket = FundamentalBranchSocket<Float_t>;
using DoubleBranchSocket = FundamentalBranchSocket<Double_t>;
using LongBranchSocket = FundamentalBranchSocket<Long64_t>;
using ULongBranchSocket = FundamentalBranchSocket<ULong64_t>;
using BoolBranchSocket = FundamentalBranchSocket<Bool_t>;

} // namespace MACE::DataModel::BranchSocket

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.inl"
