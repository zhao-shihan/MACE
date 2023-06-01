#pragma once

#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/DataModel/BranchSocket2/BranchSocketBase2.h++"
#include "MACE/Utility/ROOTUtil/LeafTypeCode.h++"
#include "MACE/Utility/VectorAssign.h++"

#include "RtypesCore.h"

#include "gsl/gsl"

#include <algorithm>
#include <array>
#include <string>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

template<Concept::ROOTFundamental T, std::size_t N>
class VectorBranchSocket2 final : public BranchSocketBase2<VectorBranchSocket2<T, N>, std::array<T, N>> {
public:
    VectorBranchSocket2(std::string name, std::string title, std::array<T, N> defaultValue);

    const auto& Value() const { return fVector; }
    template<Concept::NumericVectorAny<N> V>
    auto Value() const { return VectorCast<V>(fVector); }
    void Value(auto&& v) { fVector <<= std::forward<decltype(v)>(v); }

    void CreateBranch(TTree& tree) { this->DoCreateBranch(tree, &fVector); }
    void ConnectToBranch(TTree& tree) { this->DoConnectToBranch(tree, fVector.data()); }

private:
    std::array<T, N> fVector;
};

using Vector2FBranchSocket2 = VectorBranchSocket2<Float_t, 2>;
using Vector3FBranchSocket2 = VectorBranchSocket2<Float_t, 3>;
using Vector4FBranchSocket2 = VectorBranchSocket2<Float_t, 4>;
using Vector2DBranchSocket2 = VectorBranchSocket2<Double_t, 2>;
using Vector3DBranchSocket2 = VectorBranchSocket2<Double_t, 3>;
using Vector4DBranchSocket2 = VectorBranchSocket2<Double_t, 4>;

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/VectorBranchSocket2.inl"
