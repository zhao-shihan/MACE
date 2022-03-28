#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/Vector2BranchSocket.hxx"
#include "Core/DataModel/DataHub.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::Vector2FBranchSocket;

class SpectrometerHit : public ITransientData {
    friend DataHub;
    using Base = ITransientData;

public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit(SpectrometerHit&& hit) noexcept = default;
    virtual ~SpectrometerHit() noexcept = default;
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetDriftDistance() const { return fDriftDistance; }
    [[nodiscard]] const auto& GetHitPositionZ() const { return fHitPositionZ; }
    [[nodiscard]] const auto& GetDriftDistanceVariance() const { return fDriftDistanceVariance; }
    [[nodiscard]] const auto& GetHitPositionZVariance() const { return fHitPositionZVariance; }
    [[nodiscard]] const auto& GetCellID() const { return fCellID; }
    [[nodiscard]] const auto& GetLayerID() const { return fLayerID; }
    [[nodiscard]] const auto& GetWirePosition() const { return fWirePosition; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetDriftDistance(Double_t d) { fDriftDistance = d; }
    void SetHitPositionZ(Double_t z) { fHitPositionZ = z; }
    void SetDriftDistanceVariance(Double_t var) { fDriftDistanceVariance = var; }
    void SetHitPositionZVariance(Double_t var) { fHitPositionZVariance = var; }
    void SetCellID(Int_t val) { fCellID = val; }
    void SetLayerID(Int_t val) { fLayerID = val; }
    template<typename Vector2_t>
    void SetWirePosition(Vector2_t&& pos) { fWirePosition = std::forward<Vector2_t>(pos); }
    void SetWirePosition(Double_t x, Double_t y) { fWirePosition.Set(x, y); }

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
    TEveVector2D fWirePosition;

    static DoubleBranchSocket fgHitTime;
    static FloatBranchSocket fgDriftDistance;
    static FloatBranchSocket fgHitPositionZ;
    static FloatBranchSocket fgDriftDistanceVariance;
    static FloatBranchSocket fgHitPositionZVariance;
    static IntBranchSocket fgCellID;
    static IntBranchSocket fgLayerID;
    static Vector2FBranchSocket fgWirePosition;
};

template<class Hit_t>
concept IsSpectormeterHit = std::derived_from<Hit_t, SpectrometerHit>;

} // namespace MACE::Core::DataModel::Hit
