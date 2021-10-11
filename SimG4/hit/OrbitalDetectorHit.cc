#include "SimG4/hit/OrbitalDetectorHit.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, VertexTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, VertexPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, VertexPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, VertexPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, TrackID, -1);

G4Allocator<OrbitalDetectorHit>* MACE::SimG4::Hit::AllocatorOfOrbitalDetector = nullptr;

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    G4VHit(),
    DataModel::Hit::OrbitalDetectorHit(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::OrbitalDetectorHit(hit),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::OrbitalDetectorHit(std::move(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::OrbitalDetectorHit::operator=(hit);
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::OrbitalDetectorHit::operator=(std::move(hit));
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetectorHit::CreateBranches(tree);
    tree->Branch("VertexTime", &persistVertexTime);
    tree->Branch("VertexPositionX", &persistVertexPositionX);
    tree->Branch("VertexPositionY", &persistVertexPositionY);
    tree->Branch("VertexPositionZ", &persistVertexPositionZ);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void OrbitalDetectorHit::FillBranches() {
    DataModel::Hit::OrbitalDetectorHit::FillBranches();
    persistVertexTime = fVertexTime;
    persistVertexPositionX = fVertexPosition.x();
    persistVertexPositionY = fVertexPosition.y();
    persistVertexPositionZ = fVertexPosition.z();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}