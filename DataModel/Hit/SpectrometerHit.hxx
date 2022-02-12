#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::SpectrometerHit :
    private MACE::DataModel::Interface::Data {
public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept;
    SpectrometerHit(SpectrometerHit&& hit) noexcept;
    virtual ~SpectrometerHit() noexcept {}
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept;

    static constexpr const char* Name() { return "CDCHit"; }
    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetHitTime() const { return fHitTime; }
    const auto& GetWirePosition() const { return fWirePosition; }
    const auto& GetDriftDistance() const { return fDriftDistance; }
    const auto& GetDriftDistanceVariance() const { return fDriftDistanceVariance; }
    const auto& GetHitPositionZ() const { return fHitPositionZ; }
    const auto& GetHitPositionZVariance() const { return fHitPositionZVariance; }
    const auto& GetCellID() const { return fCellID; }
    const auto& GetLayerID() const { return fLayerID; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetWirePosition(const TEveVector2D& val) { fWirePosition = val; }
    void SetWirePosition(TEveVector2D&& val) { fWirePosition = std::move(val); }
    void SetWirePosition(Double_t x, Double_t y) { fWirePosition.fX = x; fWirePosition.fY = y; }
    void SetDriftDistance(Double_t d) { fDriftDistance = d; }
    void SetDriftDistanceVariance(Double_t var) { fDriftDistanceVariance = var; }
    void SetHitPositionZ(Double_t z) { fHitPositionZ = z; }
    void SetHitPositionZVariance(Double_t var) { fHitPositionZVariance = var; }
    void SetCellID(Int_t val) { fCellID = val; }
    void SetLayerID(Int_t val) { fLayerID = val; }

private:
    Double_t fHitTime;
    TEveVector2D fWirePosition;
    Double_t fDriftDistance;
    Double_t fDriftDistanceVariance;
    Double_t fHitPositionZ;
    Double_t fHitPositionZVariance;
    Int_t fCellID;
    Int_t fLayerID;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgWirePositionX;
    static Column<Float_t> fgWirePositionY;
    static Column<Float_t> fgDriftDistance;
    static Column<Float_t> fgDriftDistanceVariance;
    static Column<Float_t> fgHitPositionZ;
    static Column<Float_t> fgHitPositionZVariance;
    static Column<Int_t> fgCellID;
    static Column<Int_t> fgLayerID;
};

inline void MACE::DataModel::SpectrometerHit::FillBranches() noexcept {
    Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgWirePositionX.value = fWirePosition.fX;
    fgWirePositionY.value = fWirePosition.fY;
    fgDriftDistance.value = fDriftDistance;
    fgHitPositionZ.value = fHitPositionZ;
    fgCellID.value = fCellID;
    fgLayerID.value = fLayerID;
}
