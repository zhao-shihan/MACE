#pragma once

#include "Core/DataModel/IBranchSocket.hxx"
#include "FundamentalROOTTypeTraits.hxx"

#include "TEveVector.h"

namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
class Vector2BranchSocket final : public IBranchSocket<TEveVector2T<Fund_t>> {
public:
    Vector2BranchSocket(const TString& branchName, const std::array<TString, 2>& leafList, const std::array<Fund_t, 2>& defaultValues);
    ~Vector2BranchSocket() noexcept = default;
    Vector2BranchSocket(const Vector2BranchSocket&) = delete;
    Vector2BranchSocket& operator=(const Vector2BranchSocket&) = delete;

    [[nodiscard]] const TEveVector2T<Fund_t>& GetValue() const override { return fVector2; }
    void SetValue(const TEveVector2T<Fund_t>& vector2) override { fVector2 = vector2; }

    void CreateBranch(TTree& tree) override { tree.Branch(this->fBranchName, fVector2.Arr(), fLeafList); }
    void ConnectToBranch(TTree& tree) override { tree.SetBranchAddress(this->fBranchName, fVector2.Arr()); }

private:
    const TString fLeafList;
    TEveVector2T<Fund_t> fVector2;
};

using Vector2FBranchSocket = Vector2BranchSocket<Float_t>;

} // namespace MACE::Core::DataModel::BranchSocket

#include "Core/DataModel/BranchSocket/Vector2BranchSocket.ixx"
