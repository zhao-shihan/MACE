#include "hit/transient/OrbitalDetector.hh"
#include "hit/persistency/OrbitalDetector.hh"

using namespace MACE::DataModel::Hit;

Transient::OrbitalDetector::OrbitalDetector() :
    fHitPosition(),
    fVertexPosition(),
    fParticleName(nullptr),
    fHitTime(0.0),
    fVertexTime(0.0),
    fTrackID(-1) {}

Transient::OrbitalDetector::OrbitalDetector(const OrbitalDetector& hit) :
    fHitPosition(hit.fHitPosition),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fHitTime(hit.fHitTime),
    fVertexTime(hit.fVertexTime),
    fTrackID(hit.fTrackID) {}

Transient::OrbitalDetector::OrbitalDetector(OrbitalDetector&& hit) :
    fHitPosition(std::move(hit.fHitPosition)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fHitTime(std::move(hit.fHitTime)),
    fVertexTime(std::move(hit.fVertexTime)),
    fTrackID(std::move(hit.fTrackID)) {}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(const OrbitalDetector& hit) {
    fHitPosition = hit.fHitPosition;
    fVertexPosition = hit.fVertexPosition;
    fParticleName = hit.fParticleName;
    fHitTime = hit.fHitTime;
    fVertexTime = hit.fVertexTime;
    fTrackID = hit.fTrackID;
    return *this;
}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(OrbitalDetector&& hit) {
    fHitPosition = std::move(hit.fHitPosition);
    fVertexPosition = std::move(hit.fVertexPosition);
    fParticleName = std::move(hit.fParticleName);
    fHitTime = std::move(hit.fHitTime);
    fVertexTime = std::move(hit.fVertexTime);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

Transient::OrbitalDetector::OrbitalDetector(const Persistency::OrbitalDetector& hit) :
    fHitPosition(hit.HitPosition[0], hit.HitPosition[1], hit.HitPosition[2]),
    fVertexPosition(hit.VertexPosition[0], hit.VertexPosition[1], hit.VertexPosition[2]),
    fParticleName(hit.ParticleName),
    fHitTime(hit.HitTime),
    fVertexTime(hit.VertexTime),
    fTrackID(hit.TrackID) {}

Transient::OrbitalDetector::OrbitalDetector(Persistency::OrbitalDetector&& hit) :
    fHitPosition(std::move(hit.HitPosition[0]), std::move(hit.HitPosition[1]), std::move(hit.HitPosition[2])),
    fVertexPosition(std::move(hit.VertexPosition[0]), std::move(hit.VertexPosition[1]), std::move(hit.VertexPosition[2])),
    fParticleName(std::move(hit.ParticleName)),
    fHitTime(std::move(hit.HitTime)),
    fVertexTime(std::move(hit.VertexTime)),
    fTrackID(std::move(hit.TrackID)) {}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(const Persistency::OrbitalDetector& hit) {
    fHitPosition = CLHEP::Hep3Vector(hit.HitPosition[0], hit.HitPosition[1], hit.HitPosition[2]);
    fVertexPosition = CLHEP::Hep3Vector(hit.VertexPosition[0], hit.VertexPosition[1], hit.VertexPosition[2]);
    fParticleName = hit.ParticleName;
    fHitTime = hit.HitTime;
    fVertexTime = hit.VertexTime;
    fTrackID = hit.TrackID;
    return *this;
}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(Persistency::OrbitalDetector&& hit) {
    fHitPosition = CLHEP::Hep3Vector(std::move(hit.HitPosition[0]), std::move(hit.HitPosition[1]), std::move(hit.HitPosition[2]));
    fVertexPosition = CLHEP::Hep3Vector(std::move(hit.VertexPosition[0]), std::move(hit.VertexPosition[1]), std::move(hit.VertexPosition[2]));
    fParticleName = std::move(hit.ParticleName);
    fHitTime = std::move(hit.HitTime);
    fVertexTime = std::move(hit.VertexTime);
    fTrackID = std::move(hit.TrackID);
    return *this;
}

Persistency::OrbitalDetector Transient::OrbitalDetector::ToPersistency() {
    return Persistency::OrbitalDetector{
        { (float)fHitPosition.x(), (float)fHitPosition.y(), (float)fHitPosition.z() },
        { (float)fVertexPosition.x(), (float)fVertexPosition.y(), (float)fVertexPosition.z() },
        (const char*)fParticleName,
        (float)fHitTime,
        (float)fVertexTime,
        (int)fTrackID
    };
}
