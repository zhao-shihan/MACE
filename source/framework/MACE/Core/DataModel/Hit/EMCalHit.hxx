#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"

#include <string_view>

namespace MACE::Core::DataModel::Hit {

using namespace std::string_view_literals;

class EMCalHit {
public:
    EMCalHit() noexcept;
    virtual ~EMCalHit() = default;

    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& GetEnergy() const { return fEnergy; }
    const auto& GetEnergyVariance() const { return fEnergyVariance; }

    void HitTime(double val) { fHitTime = val; }
    void SetEnergy(double val) { fEnergy = val; }
    void SetEnergyVariance(double val) { fEnergyVariance = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "CalHit"sv; }

private:
    double fHitTime;
    double fEnergy;
    double fEnergyVariance;

    static BranchSocket::DoubleBranchSocket fgHitTime;
    static BranchSocket::FloatBranchSocket fgEnergy;
    static BranchSocket::FloatBranchSocket fgEnergyVariance;
};
static_assert(TransientData<EMCalHit>);

} // namespace MACE::Core::DataModel::Hit
