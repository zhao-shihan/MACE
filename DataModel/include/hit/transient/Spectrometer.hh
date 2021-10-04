#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::Hit::Transient::Spectrometer {
    MACE_DATA_MODEL_TRANSIENT_ESSENTIAL(Spectrometer);

    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, HitPosition);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, VertexPosition);
    MACE_DATA_MODEL_SMALL_MEMBER(const char*, ParticleName);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, VertexTime);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, ChamberID);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID);
};