#pragma once

#include "DataModelGlobal.hh"
#include "base/Data.hh"

class MACE::DataModel::Hit::Calorimeter :
    protected MACE::DataModel::Base::Data {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(Calorimeter);

    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, Energy);

    MACE_DATA_MODEL_PERSISTIFIER(Float_t, HitTime);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, Energy);

    MACE_DATA_MODEL_NAME("Calorimeter");

public:
    static void CreateBranches(TTree* tree);
    virtual void FillBranches() override;
};