#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;

class EMCalHit : public ITransientData {
public:
    EMCalHit() noexcept;
    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    virtual ~EMCalHit() noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;

    const auto& GetHitTime() const { return fHitTime; }
    const auto& GetEnergy() const { return fEnergy; }
    const auto& GetEnergyVariance() const { return fEnergyVariance; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetEnergy(Double_t val) { fEnergy = val; }
    void SetEnergyVariance(Double_t val) { fEnergyVariance = val; }

    static consteval const char* BasicTreeName() noexcept { return "CalHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fHitTime;
    Double_t fEnergy;
    Double_t fEnergyVariance;

    static DoubleBranchSocket fgHitTime;
    static FloatBranchSocket fgEnergy;
    static FloatBranchSocket fgEnergyVariance;
};

} // namespace MACE::Core::DataModel::Hit
