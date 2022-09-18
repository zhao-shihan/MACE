#pragma once

#include "MACE/Compatibility/Eigen34/TemplateAlias.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"
#include "MACE/Utility/Concept/FundamentalType.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "Eigen/Core"

namespace MACE::Core::DataModel::BranchSocket {

namespace Eigen34 = Compatibility::Eigen34;
using MACE::Utility::Concept::ArithmeticExcludeBoolChar;

template<ROOTFundamental T, int N>
class VectorBranchSocket final : public IBranchSocket<Eigen34::Vector<T, N>> {
public:
    VectorBranchSocket(const TString& branchName, const std::array<TString, N>& leafNames, const std::array<T, N>& defaultValues);

    const Eigen34::Vector<T, N>& Value() const override { return fVector; }
    template<ArithmeticExcludeBoolChar U>
    auto Value() const { return fVector.template cast<U>(); }
    void Value(const Eigen34::Vector<T, N>& vector) override { fVector = vector; }
    template<ArithmeticExcludeBoolChar U>
    void Value(const Eigen34::Vector<U, N>& vector) { fVector = vector.template cast<T>(); }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector.data(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector.data()); }

private:
    TString fLeafList;
    Eigen34::Vector<T, N> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.inl"
