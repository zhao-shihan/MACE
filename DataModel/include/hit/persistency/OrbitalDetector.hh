#pragma once

#include "DataModelGlobal.hh"

struct MACE::DataModel::Hit::Persistency::OrbitalDetector final {
    float       HitPosition[3];
    float       VertexPosition[3];
    const char* ParticleName;
    float       HitTime;
    float       VertexTime;
    int         TrackID;

    static constexpr const char* LeafList =
        "HitPosition[3]/F:"
        "VertexPosition[3]/F:"
        "ParticleName/C:"
        "HitTime/F:"
        "VertexTime/F:"
        "TrackID/I";
};