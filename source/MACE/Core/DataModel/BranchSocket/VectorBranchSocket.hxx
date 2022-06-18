#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.hxx"
#include "MACE/Utility/EigenCompatibility.hxx"

#include "Eigen/Core"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental ROOTFundamentalT, int Size>
class VectorBranchSocket final : public IBranchSocket<Eigen::Vector<ROOTFundamentalT, Size>> {
public:
    VectorBranchSocket(const TString& branchName, const std::array<TString, Size>& leafNames, const std::array<ROOTFundamentalT, Size>& defaultValues);
    ~VectorBranchSocket() noexcept = default;
    VectorBranchSocket(const VectorBranchSocket&) = delete;
    VectorBranchSocket& operator=(const VectorBranchSocket&) = delete;

    const Eigen::Vector<ROOTFundamentalT, Size>& GetValue() const override { return fVector; }
    void SetValue(const Eigen::Vector<ROOTFundamentalT, Size>& vector) override { fVector = vector; }
    template<typename T>
    Eigen::Vector<T, Size> GetValue() const { return fVector.template cast<T>(); }
    template<typename T>
    void SetValue(const Eigen::Vector<T, Size>& vector) { fVector = vector.template cast<ROOTFundamentalT>(); }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector.data(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector.data()); }

private:
    TString fLeafList;
    Eigen::Vector<ROOTFundamentalT, Size> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.inl"
