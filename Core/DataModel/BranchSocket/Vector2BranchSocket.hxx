#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "IsROOTFundamental.hxx"

#include "TEveVector.h"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
class Vector2BranchSocket final : public IBranchSocket<TEveVector2T<Fund_t>> {
public:
    Vector2BranchSocket(const char* branchName, std::array<const char*, 2> leafList, std::array<Fund_t, 2> defaultValues);
    ~Vector2BranchSocket() noexcept = default;
    Vector2BranchSocket(const Vector2BranchSocket&) = delete;
    Vector2BranchSocket& operator=(const Vector2BranchSocket&) = delete;

    [[nodiscard]] const TEveVector2T<Fund_t>& GetValue() const override { return fVector2; }
    void SetValue(const TEveVector2T<Fund_t>& vector2) override { fVector2 = vector2; }

    void CreateBranch(TTree& tree) override { tree.Branch(fBranchName, fVector2.Arr(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(fBranchName, fVector2.Arr()); }

private:
    const TString fBranchName;
    TString fLeafList;
    TEveVector2T<Fund_t> fVector2;
};

using Vector2FBranchSocket = Vector2BranchSocket<Float_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/Vector2BranchSocket.ixx"
