#include "SimG4/Hit/SpectrometerHit.hh"

using namespace MACE::SimG4::Hit;

Float_t SpectrometerHit::persistVertexTime = 0.0f;
std::array<Float_t, 3> SpectrometerHit::persistVertexPosition = { 0.0f, 0.0f, 0.0f };
const char* SpectrometerHit::persistParticleName = "";
int32_t SpectrometerHit::persistTrackID = -1;

G4Allocator<SpectrometerHit>* MACE::SimG4::Hit::SpectrometerHitAllocator = nullptr;

SpectrometerHit::SpectrometerHit() noexcept :
    G4VHit(),
    DataModel::Hit::SpectrometerHit(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::SpectrometerHit(static_cast<const DataModel::Hit::SpectrometerHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::SpectrometerHit(static_cast<DataModel::Hit::SpectrometerHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    G4VHit::operator=(static_cast<const G4VHit&>(hit));
    DataModel::Hit::SpectrometerHit::operator=(static_cast<const DataModel::Hit::SpectrometerHit&>(hit));
    fParticleName = hit.fParticleName;
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fTrackID = hit.fTrackID;
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    G4VHit::operator=(static_cast<G4VHit&&>(hit));
    DataModel::Hit::SpectrometerHit::operator=(static_cast<DataModel::Hit::SpectrometerHit&&>(hit));
    fParticleName = std::move(hit.fParticleName);
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    DataModel::Hit::SpectrometerHit::CreateBranches(tree);
    tree->Branch("VertexT", &persistVertexTime);
    tree->Branch("VertexX", &std::get<0>(persistVertexPosition));
    tree->Branch("VertexY", &std::get<1>(persistVertexPosition));
    tree->Branch("VertexZ", &std::get<2>(persistVertexPosition));
    tree->Branch("Particle", const_cast<char*>(persistParticleName), "Particle/C");
    tree->Branch("TrackID", &persistTrackID);
}

void SpectrometerHit::FillBranches() noexcept {
    DataModel::Hit::SpectrometerHit::FillBranches();
    persistVertexTime = fVertexTime;
    std::get<0>(persistVertexPosition) = fVertexPosition.x();
    std::get<1>(persistVertexPosition) = fVertexPosition.y();
    std::get<2>(persistVertexPosition) = fVertexPosition.z();
    persistParticleName = fParticleName.Data();
    persistTrackID = fTrackID;
}