#include "detector/hit/Spectrometer.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, VertexTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, VertexPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, VertexPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, VertexPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, TrackID, -1);

G4Allocator<Spectrometer>* MACE::SimG4::Hit::AllocatorOfSpectrometer = nullptr;

Spectrometer::Spectrometer() noexcept :
    G4VHit(),
    DataModel::Hit::Spectrometer(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

Spectrometer::Spectrometer(const Spectrometer& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::Spectrometer(hit),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

Spectrometer::Spectrometer(Spectrometer&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::Spectrometer(std::move(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

Spectrometer& Spectrometer::operator=(const Spectrometer& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::Spectrometer::operator=(hit);
    fParticleName = hit.fParticleName;
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fTrackID = hit.fTrackID;
    return *this;
}

Spectrometer& Spectrometer::operator=(Spectrometer&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::Spectrometer::operator=(std::move(hit));
    fParticleName = std::move(hit.fParticleName);
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void Spectrometer::CreateBranches(TTree* tree) {
    DataModel::Hit::Spectrometer::CreateBranches(tree);
    tree->Branch("VertexTime", &persistVertexTime);
    tree->Branch("VertexPositionX", &persistVertexPositionX);
    tree->Branch("VertexPositionY", &persistVertexPositionY);
    tree->Branch("VertexPositionZ", &persistVertexPositionZ);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void Spectrometer::FillBranches() {
    DataModel::Hit::Spectrometer::FillBranches();
    persistVertexTime = fVertexTime;
    persistVertexPositionX = fVertexPosition.x();
    persistVertexPositionY = fVertexPosition.y();
    persistVertexPositionZ = fVertexPosition.z();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}