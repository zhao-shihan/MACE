#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hh"
#include "DataModel/Interface/Data.hh"

class MACE::DataModel::OrbitalDetectorHit :
    protected MACE::DataModel::Interface::Data {
public:
    OrbitalDetectorHit() noexcept;
    OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept;
    OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept;
    virtual ~OrbitalDetectorHit() noexcept {}
    OrbitalDetectorHit& operator=(const OrbitalDetectorHit& hit) noexcept;
    OrbitalDetectorHit& operator=(OrbitalDetectorHit&& hit) noexcept;

    static constexpr const char* Name() { return "MCPHit"; }
    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    auto GetHitTime() const { return fHitTime; }
    const auto& GetHitPosition() const { return fHitPosition; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVectorD& val) { fHitPosition = val; }
    void SetHitPosition(TEveVectorD&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y, Double_t z) { fHitPosition.fX = x; fHitPosition.fY = y; fHitPosition.fZ = z; }

private:
    double_t fHitTime;
    TEveVectorD fHitPosition;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgHitPositionX;
    static Column<Float_t> fgHitPositionY;
    static Column<Float_t> fgHitPositionZ;
};

inline void MACE::DataModel::Hit::OrbitalDetectorHit::FillBranches() noexcept {
    MACE::DataModel::Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgHitPositionX.value = fHitPosition.fX;
    fgHitPositionY.value = fHitPosition.fY;
    fgHitPositionZ.value = fHitPosition.fZ;
}