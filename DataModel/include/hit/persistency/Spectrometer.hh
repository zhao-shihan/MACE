#pragma once

#include "DataModelGlobal.hh"

struct MACE::DataModel::Hit::Persistency::Spectrometer final {
    float       HitPosition[3];
    float       VertexPosition[3];
    const char* ParticleName;
    float       HitTime;
    float       VertexTime;
    int         ChamberID;
    int         TrackID;

    static constexpr const char* LeafList =
        "HitPosition[3]/F:"
        "VertexPosition[3]/F:"
        "ParticleName/C:"
        "HitTime/F:"
        "VertexTime/F:"
        "ChamberID/I:"
        "TrackID/I";
};