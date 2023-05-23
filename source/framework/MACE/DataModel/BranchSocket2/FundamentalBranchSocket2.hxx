#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"
#include "MACE/DataModel/BranchSocket2/BranchSocketBase2.hxx"

#include "RtypesCore.h"

#include <string>

namespace MACE::DataModel::inline BranchSocket {

template<Concept::ROOTFundamental T>
class FundamentalBranchSocket2 final : public BranchSocketBase2<FundamentalBranchSocket2<T>, T> {
public:
    FundamentalBranchSocket2(std::string name, std::string title, T defaultValue);

    const auto& Value() const { return fValue; }
    void Value(const auto& v) { fValue = v; }

    void CreateBranch(TTree& tree) { this->DoCreateBranch(tree, &fValue); }
    void ConnectToBranch(TTree& tree) { this->DoConnectToBranch(tree, &fValue); }

private:
    T fValue;
};

using CharBranchSocket2 = FundamentalBranchSocket2<Char_t>;
using UCharBranchSocket2 = FundamentalBranchSocket2<UChar_t>;
using ShortBranchSocket2 = FundamentalBranchSocket2<Short_t>;
using UShortBranchSocket2 = FundamentalBranchSocket2<UShort_t>;
using IntBranchSocket2 = FundamentalBranchSocket2<Int_t>;
using UIntBranchSocket2 = FundamentalBranchSocket2<UInt_t>;
using FloatBranchSocket2 = FundamentalBranchSocket2<Float_t>;
using DoubleBranchSocket2 = FundamentalBranchSocket2<Double_t>;
using LongBranchSocket2 = FundamentalBranchSocket2<Long64_t>;
using ULongBranchSocket2 = FundamentalBranchSocket2<ULong64_t>;
using BoolBranchSocket2 = FundamentalBranchSocket2<Bool_t>;

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/FundamentalBranchSocket2.inl"
