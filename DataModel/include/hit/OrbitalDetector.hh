#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include "DataModelGlobal.hh"
#include "base/Data.hh"

class MACE::DataModel::Hit::OrbitalDetector :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(OrbitalDetector);

    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, HitPosition);

    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitTime);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionX);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionY);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitPositionZ);

    MACE_DATA_MODEL_NAME("OrbitalDetector");

public:
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() override;
};