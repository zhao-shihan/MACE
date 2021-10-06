#include "hit/transient/OrbitalDetector.hh"
#include "hit/persistency/OrbitalDetector.hh"

using namespace MACE::DataModel::Hit;

Transient::OrbitalDetector::OrbitalDetector() :
    fParticleName(nullptr),
    fHitTime(0.0),
    fHitPosition(),
    fVertexTime(0.0),
    fVertexPosition(),
    fTrackID(-1) {}

Transient::OrbitalDetector::OrbitalDetector(const OrbitalDetector& hit) :
    fParticleName(hit.fParticleName),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fTrackID(hit.fTrackID) {}

Transient::OrbitalDetector::OrbitalDetector(OrbitalDetector&& hit) :
    fParticleName(std::move(hit.fParticleName)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fTrackID(std::move(hit.fTrackID)) {}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(const OrbitalDetector& hit) {
    fParticleName = hit.fParticleName;
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fTrackID = hit.fTrackID;
    return *this;
}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(OrbitalDetector&& hit) {
    fParticleName = std::move(hit.fParticleName);
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

Transient::OrbitalDetector::OrbitalDetector(const Persistency::OrbitalDetector& hit) :
    fParticleName(hit.ParticleName),
    fHitTime(hit.HitT),
    fHitPosition(hit.HitX, hit.HitY, hit.HitZ),
    fVertexTime(hit.VertexT),
    fVertexPosition(hit.VertexX, hit.VertexY, hit.VertexZ),
    fTrackID(hit.TrackID) {}

Transient::OrbitalDetector::OrbitalDetector(Persistency::OrbitalDetector&& hit) :
    fParticleName(std::move(hit.ParticleName)),
    fHitTime(std::move(hit.HitT)),
    fHitPosition(std::move(hit.HitX), std::move(hit.HitY), std::move(hit.HitZ)),
    fVertexTime(std::move(hit.VertexT)),
    fVertexPosition(std::move(hit.VertexX), std::move(hit.VertexY), std::move(hit.VertexZ)),
    fTrackID(std::move(hit.TrackID)) {}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(const Persistency::OrbitalDetector& hit) {
    fParticleName = hit.ParticleName;
    fHitTime = hit.HitT;
    fHitPosition = CLHEP::Hep3Vector(hit.HitX, hit.HitY, hit.HitZ);
    fVertexTime = hit.VertexT;
    fVertexPosition = CLHEP::Hep3Vector(hit.VertexX, hit.VertexY, hit.VertexZ);
    fTrackID = hit.TrackID;
    return *this;
}

Transient::OrbitalDetector& Transient::OrbitalDetector::operator=(Persistency::OrbitalDetector&& hit) {
    fParticleName = std::move(hit.ParticleName);
    fHitTime = std::move(hit.HitT);
    fHitPosition = CLHEP::Hep3Vector(std::move(hit.HitX), std::move(hit.HitY), std::move(hit.HitZ));
    fVertexTime = std::move(hit.VertexT);
    fVertexPosition = CLHEP::Hep3Vector(std::move(hit.VertexX), std::move(hit.VertexY), std::move(hit.VertexZ));
    fTrackID = std::move(hit.TrackID);
    return *this;
}

Persistency::OrbitalDetector Transient::OrbitalDetector::ToPersistency() {
    return Persistency::OrbitalDetector{
        (const char*)fParticleName,
        (float)fHitTime,
        (float)fHitPosition.x(),
        (float)fHitPosition.y(),
        (float)fHitPosition.z(),
        (float)fVertexTime,
        (float)fVertexPosition.x(),
        (float)fVertexPosition.y(),
        (float)fVertexPosition.z(),
        (int)fTrackID
    };
}
