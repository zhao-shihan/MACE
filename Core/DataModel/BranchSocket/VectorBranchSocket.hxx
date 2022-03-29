#pragma once

#include "Core/DataModel/BranchSocket/FundamentalROOTTypeTraits.hxx"
#include "Core/DataModel/IBranchSocket.hxx"
#include "Utility/EigenCompatibility.hxx"

#include "Eigen/Core"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t, int Size>
class VectorBranchSocket final : public IBranchSocket<Eigen::Vector<Fund_t, Size>> {
public:
    VectorBranchSocket(const TString& branchName, const std::array<TString, Size>& leafList, const std::array<Fund_t, Size>& defaultValues);
    ~VectorBranchSocket() noexcept = default;
    VectorBranchSocket(const VectorBranchSocket&) = delete;
    VectorBranchSocket& operator=(const VectorBranchSocket&) = delete;

    [[nodiscard]] const Eigen::Vector<Fund_t, Size>& GetValue() const override { return fVector; }
    void SetValue(const Eigen::Vector<Fund_t, Size>& vector) override { fVector = vector; }
    template<typename T>
    [[nodiscard]] Eigen::Vector<T, Size> GetValue() const { return fVector.template cast<T>(); }
    template<typename T>
    void SetValue(const Eigen::Vector<T, Size>& vector) { fVector = vector.template cast<Fund_t>(); }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector.data(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector.data()); }

private:
    TString fLeafList;
    Eigen::Vector<Fund_t, Size> fVector;
};

using Vector2FBranchSocket = VectorBranchSocket<Float_t, 2>;
using Vector3FBranchSocket = VectorBranchSocket<Float_t, 3>;
using Vector4FBranchSocket = VectorBranchSocket<Float_t, 4>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/VectorBranchSocket.ixx"
