#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/DataModel/BranchSocketBase2.hxx"
#include "MACE/Utility/ROOTUtil/LeafTypeCode.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include "TTree.h"

#include "gsl/gsl"

#include <algorithm>
#include <array>
#include <string>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

template<Concept::Arithmetic T, std::size_t N>
class VectorBranchSocket2 final : public BranchSocketBase2<VectorBranchSocket2<T, N>, std::array<T, N>> {
public:
    VectorBranchSocket2(std::string name, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValue);

    const auto& Value() const { return fVector; }
    void Value(auto&& v) { VectorAssign(fVector, std::forward<decltype(v)>(v)); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fName.c_str(), fVector.data(), fLeafList.c_str()); }
    // void CreateBranch(TTree& tree) { tree.Branch(this->fName.c_str(), &fVector); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fName.c_str(), fVector.data()); }

private:
    const std::string fLeafList;
    std::array<T, N> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket2<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket2<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket2<Float_t, 4>;
using Vector2DBranchSocket = VectorBranchSocket2<Double_t, 2>;
using Vector3DBranchSocket = VectorBranchSocket2<Double_t, 3>;
using Vector4DBranchSocket = VectorBranchSocket2<Double_t, 4>;

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/VectorBranchSocket2.inl"
