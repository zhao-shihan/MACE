#include "hit/transient/Spectrometer.hh"
#include "hit/persistency/Spectrometer.hh"

using namespace MACE::DataModel::Hit;

Transient::Spectrometer::Spectrometer() :
    fHitPosition(),
    fVertexPosition(),
    fParticleName(nullptr),
    fHitTime(0.0),
    fVertexTime(0.0),
    fChamberID(-1),
    fTrackID(-1) {}

Transient::Spectrometer::Spectrometer(const Spectrometer& hit) :
    fHitPosition(hit.fHitPosition),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fHitTime(hit.fHitTime),
    fVertexTime(hit.fVertexTime),
    fChamberID(hit.fChamberID),
    fTrackID(hit.fTrackID) {}

Transient::Spectrometer::Spectrometer(Spectrometer&& hit) :
    fHitPosition(std::move(hit.fHitPosition)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fHitTime(std::move(hit.fHitTime)),
    fVertexTime(std::move(hit.fVertexTime)),
    fChamberID(std::move(hit.fChamberID)),
    fTrackID(std::move(hit.fTrackID)) {}

Transient::Spectrometer& Transient::Spectrometer::operator=(const Spectrometer& hit) {
    fHitPosition = hit.fHitPosition;
    fVertexPosition = hit.fVertexPosition;
    fParticleName = hit.fParticleName;
    fHitTime = hit.fHitTime;
    fVertexTime = hit.fVertexTime;
    fChamberID = hit.fChamberID;
    fTrackID = hit.fTrackID;
    return *this;
}

Transient::Spectrometer& Transient::Spectrometer::operator=(Spectrometer&& hit) {
    fHitPosition = std::move(hit.fHitPosition);
    fVertexPosition = std::move(hit.fVertexPosition);
    fParticleName = std::move(hit.fParticleName);
    fHitTime = std::move(hit.fHitTime);
    fVertexTime = std::move(hit.fVertexTime);
    fChamberID = std::move(hit.fChamberID);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

Transient::Spectrometer::Spectrometer(const Persistency::Spectrometer& hit) :
    fHitPosition(hit.HitPosition[0], hit.HitPosition[1], hit.HitPosition[2]),
    fVertexPosition(hit.VertexPosition[0], hit.VertexPosition[1], hit.VertexPosition[2]),
    fParticleName(hit.ParticleName),
    fHitTime(hit.HitTime),
    fVertexTime(hit.VertexTime),
    fChamberID(hit.ChamberID),
    fTrackID(hit.TrackID) {}

Transient::Spectrometer::Spectrometer(Persistency::Spectrometer&& hit) :
    fHitPosition(std::move(hit.HitPosition[0]), std::move(hit.HitPosition[1]), std::move(hit.HitPosition[2])),
    fVertexPosition(std::move(hit.VertexPosition[0]), std::move(hit.VertexPosition[1]), std::move(hit.VertexPosition[2])),
    fParticleName(std::move(hit.ParticleName)),
    fHitTime(std::move(hit.HitTime)),
    fVertexTime(std::move(hit.VertexTime)),
    fChamberID(std::move(hit.ChamberID)),
    fTrackID(std::move(hit.TrackID)) {}

Transient::Spectrometer& Transient::Spectrometer::operator=(const Persistency::Spectrometer& hit) {
    fHitPosition = CLHEP::Hep3Vector(hit.HitPosition[0], hit.HitPosition[1], hit.HitPosition[2]);
    fVertexPosition = CLHEP::Hep3Vector(hit.VertexPosition[0], hit.VertexPosition[1], hit.VertexPosition[2]);
    fParticleName = hit.ParticleName;
    fHitTime = hit.HitTime;
    fVertexTime = hit.VertexTime;
    fChamberID = hit.ChamberID;
    fTrackID = hit.TrackID;
    return *this;
}

Transient::Spectrometer& Transient::Spectrometer::operator=(Persistency::Spectrometer&& hit) {
    fHitPosition = CLHEP::Hep3Vector(std::move(hit.HitPosition[0]), std::move(hit.HitPosition[1]), std::move(hit.HitPosition[2]));
    fVertexPosition = CLHEP::Hep3Vector(std::move(hit.VertexPosition[0]), std::move(hit.VertexPosition[1]), std::move(hit.VertexPosition[2]));
    fParticleName = std::move(hit.ParticleName);
    fHitTime = std::move(hit.HitTime);
    fVertexTime = std::move(hit.VertexTime);
    fChamberID = std::move(hit.ChamberID);
    fTrackID = std::move(hit.TrackID);
    return *this;
}

Persistency::Spectrometer Transient::Spectrometer::ToPersistency() {
    return Persistency::Spectrometer{
        { (float)fHitPosition.x(), (float)fHitPosition.y(), (float)fHitPosition.z() },
        { (float)fVertexPosition.x(), (float)fVertexPosition.y(), (float)fVertexPosition.z() },
        (const char*)fParticleName,
        (float)fHitTime,
        (float)fVertexTime,
        (int)fChamberID,
        (int)fTrackID
    };
}
