#pragma once

#include "DataModelGlobal.hh"

struct MACE::DataModel::Hit::Persistency::OrbitalDetector final {
    const char* ParticleName;
    float       HitT;
    float       HitX;
    float       HitY;
    float       HitZ;
    float       VertexT;
    float       VertexX;
    float       VertexY;
    float       VertexZ;
    int         TrackID;

    static constexpr const char* LeafList =
        "ParticleName/C:"
        "HitT/F:"
        "HitX/F:"
        "HitY/F:"
        "HitZ/F:"
        "VertexT/F:"
        "VertexX/F:"
        "VertexY/F:"
        "VertexZ/F:"
        "TrackID/I";
};