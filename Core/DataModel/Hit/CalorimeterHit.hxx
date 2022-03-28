#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/DataHub.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;

class CalorimeterHit : public ITransientData {
    friend DataHub;

public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept = default;
    CalorimeterHit(CalorimeterHit&& hit) noexcept = default;
    virtual ~CalorimeterHit() noexcept = default;
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept = default;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetEnergy() const { return fEnergy; }
    [[nodiscard]] const auto& GetEnergyVariance() const { return fEnergyVariance; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetEnergy(Double_t val) { fEnergy = val; }
    void SetEnergyVariance(Double_t val) { fEnergyVariance = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CalHit"; }

private:
    Double_t fHitTime;
    Double_t fEnergy;
    Double_t fEnergyVariance;

    static DoubleBranchSocket fgHitTime;
    static FloatBranchSocket fgEnergy;
    static FloatBranchSocket fgEnergyVariance;
};

} // namespace MACE::Core::DataModel::Hit
