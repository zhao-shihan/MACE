#pragma once

#include "DataModelGlobal.hh"

struct MACE::DataModel::Hit::Persistency::Calorimeter final {
    const char* ParticleName;
    float       HitTime;
    float       Energy;
    int         TrackID;

    static constexpr const char* LeafList =
        "ParticleName/C:"
        "HitTime/F:"
        "Energy/F:"
        "TrackID/I";
};