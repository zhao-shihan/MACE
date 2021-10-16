#include "SimG4/Hit/OrbitalDetectorHit.hh"

using namespace MACE::SimG4::Hit;

Float_t OrbitalDetectorHit::persistVertexTime = 0.0f;
std::array<Float_t, 3> OrbitalDetectorHit::persistVertexPosition = { 0.0f, 0.0f, 0.0f };
TString OrbitalDetectorHit::persistParticleName = "";
int32_t OrbitalDetectorHit::persistTrackID = -1;

G4Allocator<OrbitalDetectorHit>* MACE::SimG4::Hit::OrbitalDetectorAllocator = nullptr;

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    G4VHit(),
    DataModel::Hit::OrbitalDetectorHit(),
    fVertexTime(0.0),
    fVertexPosition(),
    fParticleName(nullptr),
    fTrackID(-1) {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::OrbitalDetectorHit(static_cast<const DataModel::Hit::OrbitalDetectorHit&>(hit)),
    fVertexTime(hit.fVertexTime),
    fVertexPosition(hit.fVertexPosition),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::OrbitalDetectorHit(static_cast<DataModel::Hit::OrbitalDetectorHit&&>(hit)),
    fVertexTime(std::move(hit.fVertexTime)),
    fVertexPosition(std::move(hit.fVertexPosition)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
    G4VHit::operator=(static_cast<const G4VHit&>(hit));
    DataModel::Hit::OrbitalDetectorHit::operator=(static_cast<const DataModel::Hit::OrbitalDetectorHit&>(hit));
    fVertexTime = hit.fVertexTime;
    fVertexPosition = hit.fVertexPosition;
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
    G4VHit::operator=(static_cast<G4VHit&&>(hit));
    DataModel::Hit::OrbitalDetectorHit::operator=(static_cast<DataModel::Hit::OrbitalDetectorHit&&>(hit));
    fVertexTime = std::move(hit.fVertexTime);
    fVertexPosition = std::move(hit.fVertexPosition);
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetectorHit::CreateBranches(tree);
    tree->Branch("VertexT", &persistVertexTime);
    tree->Branch("VertexX", &std::get<0>(persistVertexPosition));
    tree->Branch("VertexY", &std::get<1>(persistVertexPosition));
    tree->Branch("VertexZ", &std::get<2>(persistVertexPosition));
    tree->Branch("Particle", const_cast<char*>(persistParticleName.Data()), "Particle/C");
    tree->Branch("TrackID", &persistTrackID);
}