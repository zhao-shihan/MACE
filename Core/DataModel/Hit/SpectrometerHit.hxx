#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/DataFactory.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;

class SpectrometerHit : public ITransientData {
    friend DataFactory;
    using Base = ITransientData;

public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit(SpectrometerHit&& hit) noexcept = default;
    virtual ~SpectrometerHit() noexcept = default;
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept = default;

    const auto& GetHitTime() const { return fHitTime; }
    const auto& GetDriftDistance() const { return fDriftDistance; }
    const auto& GetHitPositionZ() const { return fHitPositionZ; }
    const auto& GetDriftDistanceVariance() const { return fDriftDistanceVariance; }
    const auto& GetHitPositionZVariance() const { return fHitPositionZVariance; }
    const auto& GetCellID() const { return fCellID; }
    const auto& GetLayerID() const { return fLayerID; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetDriftDistance(Double_t d) { fDriftDistance = d; }
    void SetHitPositionZ(Double_t z) { fHitPositionZ = z; }
    void SetDriftDistanceVariance(Double_t var) { fDriftDistanceVariance = var; }
    void SetHitPositionZVariance(Double_t var) { fHitPositionZVariance = var; }
    void SetCellID(Int_t val) { fCellID = val; }
    void SetLayerID(Int_t val) { fLayerID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CDCHit"; }

private:
    Double_t fHitTime;
    Double_t fDriftDistance;
    Double_t fHitPositionZ;
    Double_t fDriftDistanceVariance;
    Double_t fHitPositionZVariance;
    Int_t fCellID;
    Int_t fLayerID;

    static DoubleBranchSocket fgHitTime;
    static FloatBranchSocket fgDriftDistance;
    static FloatBranchSocket fgHitPositionZ;
    static FloatBranchSocket fgDriftDistanceVariance;
    static FloatBranchSocket fgHitPositionZVariance;
    static IntBranchSocket fgCellID;
    static IntBranchSocket fgLayerID;
};

} // namespace MACE::Core::DataModel::Hit
