#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"
#include "MACE/Utility/Concept/FundamentalType.hxx"
#include "MACE/Utility/EigenCompatibility.hxx"

#include "Eigen/Core"

namespace MACE::Core::DataModel::BranchSocket {

using MACE::Utility::Concept::ArithmeticExcludeBoolChar;

template<IsROOTFundamental AROOTFundamental, int Size>
class VectorBranchSocket final : public IBranchSocket<Eigen::Vector<AROOTFundamental, Size>> {
public:
    VectorBranchSocket(const TString& branchName, const std::array<TString, Size>& leafNames, const std::array<AROOTFundamental, Size>& defaultValues);
    ~VectorBranchSocket() = default;
    VectorBranchSocket(const VectorBranchSocket&) = delete;
    VectorBranchSocket& operator=(const VectorBranchSocket&) = delete;

    const Eigen::Vector<AROOTFundamental, Size>& GetValue() const override { return fVector; }
    void SetValue(const Eigen::Vector<AROOTFundamental, Size>& vector) override { fVector = vector; }
    template<ArithmeticExcludeBoolChar T>
    Eigen::Vector<T, Size> GetValue() const { return fVector.template cast<T>(); }
    template<ArithmeticExcludeBoolChar T>
    void SetValue(const Eigen::Vector<T, Size>& vector) { fVector = vector.template cast<AROOTFundamental>(); }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector.data(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector.data()); }

private:
    TString fLeafList;
    Eigen::Vector<AROOTFundamental, Size> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.inl"
