#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::SpectrometerHit :
    protected MACE::DataModel::Interface::Data {
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

    auto GetHitTime() const { return fHitTime; }
    const auto& GetWirePosition() const { return fWirePosition; }
    auto GetDriftDistance() const { return fDriftDistance; }
    auto GetHitPositionZ() const { return fHitPositionZ; }
    auto GetCellID() const { return fCellID; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetWirePosition(const TEveVector2D& val) { fWirePosition = val; }
    void SetWirePosition(TEveVector2D&& val) { fWirePosition = std::move(val); }
    void SetWirePosition(Double_t x, Double_t y) { fWirePosition.fX = x; fWirePosition.fY = y; }
    void SetDriftDistance(Double_t r) { fDriftDistance = r; }
    void SetHitPositionZ(Double_t z) { fHitPositionZ = z; }
    void SetCellID(Int_t val) { fCellID = val; }

private:
    Double_t fHitTime;
    TEveVector2D fWirePosition;
    Double_t fDriftDistance;
    Double_t fHitPositionZ;
    Int_t fCellID;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgWirePositionX;
    static Column<Float_t> fgWirePositionY;
    static Column<Float_t> fgDriftDistance;
    static Column<Float_t> fgHitPositionZ;
    static Column<Int_t> fgCellID;
};

inline void MACE::DataModel::Hit::SpectrometerHit::FillBranches() noexcept {
    MACE::DataModel::Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgWirePositionX.value = fWirePosition.fX;
    fgWirePositionY.value = fWirePosition.fY;
    fgDriftDistance.value = fDriftDistance;
    fgHitPositionZ.value = fHitPositionZ;
    fgCellID.value = fCellID;
}