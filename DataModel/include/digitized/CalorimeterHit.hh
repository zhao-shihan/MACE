#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::Digitized::CalorimeterHit {
public:
    CalorimeterHit() {}
    virtual ~CalorimeterHit() {}

    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID, -1);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, HitTime, 0.0);
    MACE_DATA_MODEL_SMALL_MEMBER(double_t, Energy, 0.0);
    MACE_DATA_MODEL_SMALL_MEMBER(const char*, ParticleName, nullptr);
};