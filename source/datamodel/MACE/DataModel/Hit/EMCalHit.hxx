#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/DataModel/TransientData.hxx"

#include <string_view>

namespace MACE::DataModel::Hit {

class EMCalHit {
public:
    inline EMCalHit() noexcept;
    virtual ~EMCalHit() = default;

    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& Energy() const { return fEnergy; }

    void HitTime(double val) { fHitTime = val; }
    void Energy(double val) { fEnergy = val; }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("CalHit"); }

private:
    double fHitTime;
    double fEnergy;

    static BranchSocket::DoubleBranchSocket fgHitTime;
    static BranchSocket::FloatBranchSocket fgEnergy;
};
static_assert(TransientData<EMCalHit>);

} // namespace MACE::DataModel::Hit

#include "MACE/DataModel/Hit/EMCalHit.inl"
