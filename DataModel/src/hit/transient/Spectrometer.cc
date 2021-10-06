#include "hit/transient/Spectrometer.hh"
#include "hit/persistency/Spectrometer.hh"

using namespace MACE::DataModel::Hit;

Transient::Spectrometer::Spectrometer() :
    fParticleName(nullptr),
    fHitTime(0.0),
    fHitPosition(),
    fVertexTime(0.0),
    fVertexPosition(),
    fChamberID(-1),
    fTrackID(-1) {}

Transient::Spectrometer::Spectrometer(const Spectrometer& hit) :
    fParticleName(hit.fParticleName),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fChamberID(hit.fChamberID),
    fTrackID(hit.fTrackID) {}

Transient::Spectrometer::Spectrometer(Spectrometer&& hit) :
    fParticleName(std::move(hit.fParticleName)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fChamberID(std::move(hit.fChamberID)),
    fTrackID(std::move(hit.fTrackID)) {}

Transient::Spectrometer& Transient::Spectrometer::operator=(const Spectrometer& hit) {
    fParticleName = hit.fParticleName;
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fChamberID = hit.fChamberID;
    fTrackID = hit.fTrackID;
    return *this;
}

Transient::Spectrometer& Transient::Spectrometer::operator=(Spectrometer&& hit) {
    fParticleName = std::move(hit.fParticleName);
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fChamberID = std::move(hit.fChamberID);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

Transient::Spectrometer::Spectrometer(const Persistency::Spectrometer& hit) :
    fParticleName(hit.ParticleName),
    fHitTime(hit.HitT),
    fHitPosition(hit.HitX, hit.HitY, hit.HitZ),
    fVertexTime(hit.VertexT),
    fVertexPosition(hit.VertexX, hit.VertexY, hit.VertexZ),
    fChamberID(hit.ChamberID),
    fTrackID(hit.TrackID) {}

Transient::Spectrometer::Spectrometer(Persistency::Spectrometer&& hit) :
    fParticleName(std::move(hit.ParticleName)),
    fHitTime(std::move(hit.HitT)),
    fHitPosition(std::move(hit.HitX), std::move(hit.HitY), std::move(hit.HitZ)),
    fVertexTime(std::move(hit.VertexT)),
    fVertexPosition(std::move(hit.VertexX), std::move(hit.VertexY), std::move(hit.VertexZ)),
    fChamberID(std::move(hit.ChamberID)),
    fTrackID(std::move(hit.TrackID)) {}

Transient::Spectrometer& Transient::Spectrometer::operator=(const Persistency::Spectrometer& hit) {
    fParticleName = hit.ParticleName;
    fHitTime = hit.HitT;
    fHitPosition = CLHEP::Hep3Vector(hit.HitX, hit.HitY, hit.HitZ);
    fVertexTime = hit.VertexT;
    fVertexPosition = CLHEP::Hep3Vector(hit.VertexX, hit.VertexY, hit.VertexZ);
    fChamberID = hit.ChamberID;
    fTrackID = hit.TrackID;
    return *this;
}

Transient::Spectrometer& Transient::Spectrometer::operator=(Persistency::Spectrometer&& hit) {
    fParticleName = std::move(hit.ParticleName);
    fHitTime = std::move(hit.HitT);
    fHitPosition = CLHEP::Hep3Vector(std::move(hit.HitX), std::move(hit.HitY), std::move(hit.HitZ));
    fVertexTime = std::move(hit.VertexT);
    fVertexPosition = CLHEP::Hep3Vector(std::move(hit.VertexX), std::move(hit.VertexY), std::move(hit.VertexZ));
    fChamberID = std::move(hit.ChamberID);
    fTrackID = std::move(hit.TrackID);
    return *this;
}

Persistency::Spectrometer Transient::Spectrometer::ToPersistency() {
    return Persistency::Spectrometer{
        (const char*)fParticleName,
        (float)fHitTime,
        (float)fHitPosition.x(),
        (float)fHitPosition.y(),
        (float)fHitPosition.z(),
        (float)fVertexTime,
        (float)fVertexPosition.x(),
        (float)fVertexPosition.y(),
        (float)fVertexPosition.z(),
        (int)fChamberID,
        (int)fTrackID
    };
}
