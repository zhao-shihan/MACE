#pragma once

#include "TEveVector.h"

#include "DataModel/Interface/BranchSocket.hxx"

template<MACE::DataModel::FundamentalType Fund_t>
class MACE::DataModel::Vector3BranchSocket final :
    public MACE::DataModel::Interface::BranchSocket<TEveVectorT<Fund_t>> {
public:
    Vector3BranchSocket(const char* branchName, std::array<const char*, 3> leafList, std::array<Fund_t, 3> defaultValues);
    ~Vector3BranchSocket() noexcept = default;
    Vector3BranchSocket(const Vector3BranchSocket&) = delete;
    Vector3BranchSocket& operator=(const Vector3BranchSocket&) = delete;

    [[nodiscard]] const TEveVectorT<Fund_t>& GetValue() const override { return fVector3; }
    void SetValue(const TEveVectorT<Fund_t>& vector3) override { fVector3 = vector3; }

    virtual void CreateBranch(TTree& tree) { tree.Branch(fBranchName, fVector3.Arr(), fLeafList); }
    virtual void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(fBranchName, fVector3.Arr()); }

private:
    const TString       fBranchName;
    TString             fLeafList;
    TEveVectorT<Fund_t> fVector3;
};

#include "DataModel/BranchSocket/Vector3BranchSocket.ixx"

namespace MACE::DataModel::inline BranchSocket{
    using Vector3FBranchSocket = Vector3BranchSocket<Float_t>;
}
