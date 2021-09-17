#include "Hit.hh"

using namespace MACE::TrackReconstruction;

Hit::Hit(Int_t trackID, Int_t chamberID, Double_t vertexTime, const TVector3& vertexPosition, Double_t hitTime, const TVector3& hitPosition) :
    fTrackID(trackID),
    fChamberID(chamberID),
    fVertexTime(vertexTime),
    fVertexPosition(vertexPosition),
    fHitTime(hitTime),
    fHitPosition(hitPosition) {}

Hit::Hit(Hit&& hit) :
    fTrackID(std::move(hit.fTrackID)),
    fChamberID(std::move(hit.fChamberID)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}