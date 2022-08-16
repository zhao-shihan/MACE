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

template<IsROOTFundamental AROOTFundamental, int ASize>
class VectorBranchSocket final : public Utility::NonMoveableBase,
                                 public IBranchSocket<Eigen34::Vector<AROOTFundamental, ASize>> {
public:
    VectorBranchSocket(const TString& branchName, const std::array<TString, ASize>& leafNames, const std::array<AROOTFundamental, ASize>& defaultValues);

    const Eigen34::Vector<AROOTFundamental, ASize>& GetValue() const override { return fVector; }
    void SetValue(const Eigen34::Vector<AROOTFundamental, ASize>& vector) override { fVector = vector; }
    template<ArithmeticExcludeBoolChar T>
    Eigen34::Vector<T, ASize> GetValue() const { return fVector.template cast<T>(); }
    template<ArithmeticExcludeBoolChar T>
    void SetValue(const Eigen34::Vector<T, ASize>& vector) { fVector = vector.template cast<AROOTFundamental>(); }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector.data(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector.data()); }

private:
    TString fLeafList;
    Eigen34::Vector<AROOTFundamental, ASize> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.inl"
