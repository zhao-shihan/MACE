#pragma once

#include "TrackReconstructionGlobal.hh"

#define MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(T, Name) \
    public: \
        const T& Name() const { return f##Name; } \
    private: \
        T f##Name

class MACE::TrackReconstruction::Hit final {
    MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(Hit);
public:
    Hit() {}
    Hit(Int_t trackID,
        Int_t chamberID,
        Double_t vertexTime,
        const TVector3& vertexPosition,
        Double_t hitTime,
        const TVector3& hitPosition);

    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(Int_t, TrackID);
    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(Int_t, ChamberID);
    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(Double_t, VertexTime);
    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(TVector3, VertexPosition);
    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(Double_t, HitTime);
    MACE_TRACK_RECONSTRUCTION_HIT_MEMBER(TVector3, HitPosition);
};

#undef MACE_TRACK_RECONSTRUCTION_HIT_MEMBER