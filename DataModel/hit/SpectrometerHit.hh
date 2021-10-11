#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "DataModel/Global.hh"
#include "DataModel/base/Data.hh"

class MACE::DataModel::Hit::SpectrometerHit :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(SpectrometerHit);

    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, HitPosition);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, ChamberID);

    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitTime);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionX);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionY);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionZ);
    MACE_DATA_MODEL_PERSISTIFIER(Int_t, ChamberID);

    MACE_DATA_MODEL_NAME("Spectrometer");

public:
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() override;
};