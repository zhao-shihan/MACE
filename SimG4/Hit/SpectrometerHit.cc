#include "SimG4/Hit/SpectrometerHit.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, VertexTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, VertexPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, VertexPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, VertexPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, TrackID, -1);

G4Allocator<SpectrometerHit>* MACE::SimG4::Hit::AllocatorOfSpectrometer = nullptr;

SpectrometerHit::SpectrometerHit() noexcept :
    G4VHit(),
    DataModel::Hit::SpectrometerHit(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::SpectrometerHit(hit),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::SpectrometerHit(std::move(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::SpectrometerHit::operator=(hit);
    fParticleName = hit.fParticleName;
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fTrackID = hit.fTrackID;
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::SpectrometerHit::operator=(std::move(hit));
    fParticleName = std::move(hit.fParticleName);
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    DataModel::Hit::SpectrometerHit::CreateBranches(tree);
    tree->Branch("VertexTime", &persistVertexTime);
    tree->Branch("VertexPositionX", &persistVertexPositionX);
    tree->Branch("VertexPositionY", &persistVertexPositionY);
    tree->Branch("VertexPositionZ", &persistVertexPositionZ);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void SpectrometerHit::FillBranches() {
    DataModel::Hit::SpectrometerHit::FillBranches();
    persistVertexTime = fVertexTime;
    persistVertexPositionX = fVertexPosition.x();
    persistVertexPositionY = fVertexPosition.y();
    persistVertexPositionZ = fVertexPosition.z();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}