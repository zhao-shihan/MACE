#pragma once

#include "TEveVector.h"

#include "DataModel/Interface/Data.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::SpectrometerHit :
    public MACE::DataModel::Interface::Data {
    using Base = MACE::DataModel::Interface::Data;
    friend MACE::DataModel::DataHub;

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
    void SetWirePosition(const TEveVector2D& val) { fWirePosition = val; }
    void SetWirePosition(TEveVector2D&& val) { fWirePosition = std::move(val); }
    void SetWirePosition(Double_t x, Double_t y) { fWirePosition.Set(x, y); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "CDCHit"; }

private:
    Double_t     fHitTime;
    Double_t     fDriftDistance;
    Double_t     fHitPositionZ;
    Double_t     fDriftDistanceVariance;
    Double_t     fHitPositionZVariance;
    Int_t        fCellID;
    Int_t        fLayerID;
    TEveVector2D fWirePosition;

    static DoubleBranchSocket   fgHitTime;
    static FloatBranchSocket    fgDriftDistance;
    static FloatBranchSocket    fgHitPositionZ;
    static FloatBranchSocket    fgDriftDistanceVariance;
    static FloatBranchSocket    fgHitPositionZVariance;
    static IntBranchSocket      fgCellID;
    static IntBranchSocket      fgLayerID;
    static Vector2FBranchSocket fgWirePosition;
};

inline void MACE::DataModel::SpectrometerHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.Value() = fHitTime;
    fgDriftDistance.Value() = fDriftDistance;
    fgHitPositionZ.Value() = fHitPositionZ;
    fgDriftDistanceVariance.Value() = fDriftDistanceVariance;
    fgHitPositionZVariance.Value() = fHitPositionZVariance;
    fgCellID.Value() = fCellID;
    fgLayerID.Value() = fLayerID;
    fgWirePosition.Value() = fWirePosition;
}
