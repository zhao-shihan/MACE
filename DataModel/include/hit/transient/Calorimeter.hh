#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::Hit::Transient::Calorimeter {
    MACE_DATA_MODEL_TRANSIENT_ESSENTIAL(Calorimeter);

    MACE_DATA_MODEL_SMALL_MEMBER(const char*, ParticleName);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, Energy);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID);
};