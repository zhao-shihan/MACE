#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::SpectrometerHit {
public:
    SpectrometerHit() {}
    virtual ~SpectrometerHit() {}

    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID, -1);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, ChamberID, -1);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime, 0.0);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, HitPosition, CLHEP::Hep3Vector());
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, VertexTime, 0.0);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, VertexPosition, CLHEP::Hep3Vector());
    MACE_DATA_MODEL_SMALL_MEMBER(const char*, ParticleName, nullptr);
};