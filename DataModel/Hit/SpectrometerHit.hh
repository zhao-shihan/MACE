#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hh"
#include "DataModel/Interface/Data.hh"

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
    const auto& GetHitPosition() const { return fHitPosition; }
    auto GetChamberID() const { return fChamberID; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVectorD& val) { fHitPosition = val; }
    void SetHitPosition(TEveVectorD&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y, Double_t z) { fHitPosition.fX = x; fHitPosition.fY = y; fHitPosition.fZ = z; }
    void SetChamberID(Int_t val) { fChamberID = val; }

private:
    double_t fHitTime;
    TEveVectorD fHitPosition;
    Int_t fChamberID;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgHitPositionX;
    static Column<Float_t> fgHitPositionY;
    static Column<Float_t> fgHitPositionZ;
    static Column<Int_t> fgChamberID;
};

inline void MACE::DataModel::Hit::SpectrometerHit::FillBranches() noexcept {
    MACE::DataModel::Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgHitPositionX.value = fHitPosition.fX;
    fgHitPositionY.value = fHitPosition.fY;
    fgHitPositionZ.value = fHitPosition.fZ;
    fgChamberID.value = fChamberID;
}