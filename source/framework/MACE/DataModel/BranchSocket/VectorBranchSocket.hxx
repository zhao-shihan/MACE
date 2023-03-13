#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/DataModel/BranchSocketBase.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ROOTUtil/LeafTypeCode.hxx"
#include "MACE/Utility/ToSigned.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "gsl/gsl"

#include <array>
#include <string>

namespace MACE::DataModel::BranchSocket {

template<Concept::Arithmetic T, std::size_t N>
class VectorBranchSocket final : public BranchSocketBase<VectorBranchSocket<T, N>, std::array<T, N>> {
public:
    VectorBranchSocket(const std::string& branchName, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValues);

    template<Concept::Arithmetic U = T>
    auto Value() const { return VectorCast<std::array<U, N>>(fVector); }
    void Value(auto&& vector) { VectorAssign(fVector, std::forward<decltype(vector)>(vector)); }

    void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName.c_str(), fVector.data(), fLeafList.c_str()); }
    void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName.c_str(), fVector.data()); }

private:
    const std::string fLeafList;
    std::array<T, N> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;
using Vector2DBranchSocket = VectorBranchSocket<Double_t, 2>;
using Vector3DBranchSocket = VectorBranchSocket<Double_t, 3>;
using Vector4DBranchSocket = VectorBranchSocket<Double_t, 4>;

} // namespace MACE::DataModel::BranchSocket

#include "MACE/DataModel/BranchSocket/VectorBranchSocket.inl"
