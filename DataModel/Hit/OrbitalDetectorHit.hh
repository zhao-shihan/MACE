#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "DataModel/Global.hh"
#include "DataModel/Base/Data.hh"

class MACE::DataModel::Hit::OrbitalDetectorHit :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(OrbitalDetectorHit);
public:
    static constexpr const char* Name() { return "MCPHit"; }
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() noexcept override;

    auto GetHitTime() const { return fHitTime; }
    const auto& GetHitPosition() const { return fHitPosition; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetHitPosition(const CLHEP::Hep3Vector& val) { fHitPosition = val; }
    void SetHitPosition(CLHEP::Hep3Vector&& val) { fHitPosition = std::move(val); }

private:
    double_t fHitTime;
    CLHEP::Hep3Vector fHitPosition;

    static Float_t persistHitTime;
    static std::array<Float_t, 3> persistHitPosition;
};