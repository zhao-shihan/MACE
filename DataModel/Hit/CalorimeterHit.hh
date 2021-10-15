#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Base/Data.hh"

class MACE::DataModel::Hit::CalorimeterHit :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(CalorimeterHit);

    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, Energy);

    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitTime);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, Energy);

    MACE_DATA_MODEL_NAME("Calorimeter");

public:
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() override;
};