#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "DataModel/Global.hh"
#include "DataModel/Base/Data.hh"

class MACE::DataModel::Hit::SpectrometerHit :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(SpectrometerHit);
public:
    static constexpr const char* Name() { return "CDCHit"; }
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() noexcept override;

    auto GetHitTime() const { return fHitTime; }
    const auto& GetHitPosition() const { return fHitPosition; }
    auto GetChamberID() const { return fChamberID; }

    void SetHitTime(double_t val) { fHitTime = val; }
    void SetHitPosition(const CLHEP::Hep3Vector& val) { fHitPosition = val; }
    void SetHitPosition(CLHEP::Hep3Vector&& val) { fHitPosition = std::move(val); }
    void SetChamberID(int32_t val) { fChamberID = val; }

private:
    double_t fHitTime;
    CLHEP::Hep3Vector fHitPosition;
    int32_t fChamberID;

    static Float_t persistHitTime;
    static std::array<Float_t, 3> persistHitPosition;
    static Int_t persistChamberID;
};