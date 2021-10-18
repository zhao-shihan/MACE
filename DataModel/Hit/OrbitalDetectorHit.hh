#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "DataModel/Global.hh"
#include "DataModel/Core/Data.hh"

class MACE::DataModel::Hit::OrbitalDetectorHit :
    protected MACE::DataModel::Core::Data {
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
    void SetHitPosition(const CLHEP::Hep3Vector& val) { fHitPosition = val; }
    void SetHitPosition(CLHEP::Hep3Vector&& val) { fHitPosition = std::move(val); }

private:
    double_t fHitTime;
    CLHEP::Hep3Vector fHitPosition;

    static Core::Column<Float_t> fgHitTime;
    static Core::Column<Float_t> fgHitPositionX;
    static Core::Column<Float_t> fgHitPositionY;
    static Core::Column<Float_t> fgHitPositionZ;
};

void MACE::DataModel::Hit::OrbitalDetectorHit::FillBranches() noexcept {
    MACE::DataModel::Core::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgHitPositionX.value = fHitPosition.x();
    fgHitPositionY.value = fHitPosition.y();
    fgHitPositionZ.value = fHitPosition.z();
}