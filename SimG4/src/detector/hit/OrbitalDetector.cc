#include "detector/hit/OrbitalDetector.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, VertexTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, VertexPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, VertexPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, VertexPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, TrackID, -1);

G4Allocator<OrbitalDetector>* MACE::SimG4::Hit::AllocatorOfOrbitalDetector = nullptr;

OrbitalDetector::OrbitalDetector() noexcept :
    G4VHit(),
    DataModel::Hit::OrbitalDetector(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

OrbitalDetector::OrbitalDetector(const OrbitalDetector& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::OrbitalDetector(hit),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

OrbitalDetector::OrbitalDetector(OrbitalDetector&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::OrbitalDetector(std::move(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

OrbitalDetector& OrbitalDetector::operator=(const OrbitalDetector& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::OrbitalDetector::operator=(hit);
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

OrbitalDetector& OrbitalDetector::operator=(OrbitalDetector&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::OrbitalDetector::operator=(std::move(hit));
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void OrbitalDetector::CreateBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetector::CreateBranches(tree);
    tree->Branch("VertexTime", &persistVertexTime);
    tree->Branch("VertexPositionX", &persistVertexPositionX);
    tree->Branch("VertexPositionY", &persistVertexPositionY);
    tree->Branch("VertexPositionZ", &persistVertexPositionZ);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void OrbitalDetector::FillBranches() {
    DataModel::Hit::OrbitalDetector::FillBranches();
    persistVertexTime = fVertexTime;
    persistVertexPositionX = fVertexPosition.x();
    persistVertexPositionY = fVertexPosition.y();
    persistVertexPositionZ = fVertexPosition.z();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}