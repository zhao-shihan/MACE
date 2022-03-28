#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "FundamentalROOTTypeTraits.hxx"

#include "TEveVector.h"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
class Vector3BranchSocket final : public IBranchSocket<TEveVectorT<Fund_t>> {
public:
    Vector3BranchSocket(const TString& branchName, const std::array<TString, 3>& leafList, const std::array<Fund_t, 3>& defaultValues);
    ~Vector3BranchSocket() noexcept = default;
    Vector3BranchSocket(const Vector3BranchSocket&) = delete;
    Vector3BranchSocket& operator=(const Vector3BranchSocket&) = delete;

    [[nodiscard]] const TEveVectorT<Fund_t>& GetValue() const override { return fVector3; }
    void SetValue(const TEveVectorT<Fund_t>& vector3) override { fVector3 = vector3; }

    virtual void CreateBranch(TTree& tree) { tree.Branch(this->fBranchName, fVector3.Arr(), fLeafList); }
    virtual void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(this->fBranchName, fVector3.Arr()); }

private:
    const TString fLeafList;
    TEveVectorT<Fund_t> fVector3;
};

using Vector3FBranchSocket = Vector3BranchSocket<Float_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/Vector3BranchSocket.ixx"
