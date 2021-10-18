#include "SimG4/Hit/OrbitalDetectorHit.hh"

using namespace MACE::SimG4::Hit;

MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgVertexTime = { "VertexT", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgVertexPositionX = { "VertexX", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgVertexPositionY = { "VertexY", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgVertexPositionZ = { "VertexZ", 0.0f };
MACE::DataModel::Core::Column<TString> OrbitalDetectorHit::fgParticleName = { "Particle", "" };
MACE::DataModel::Core::Column<Int_t> OrbitalDetectorHit::fgTrackID = { "TrackID", -1 };

G4Allocator<OrbitalDetectorHit>* MACE::SimG4::Hit::OrbitalDetectorAllocator = nullptr;

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    G4VHit(),
    DataModel::Hit::OrbitalDetectorHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fParticleName(fgParticleName.value.Data()),
    fTrackID(fgTrackID.value) {}

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
    tree->Branch(fgVertexTime.name, &fgVertexTime.value);
    tree->Branch(fgVertexPositionX.name, &fgVertexPositionX.value);
    tree->Branch(fgVertexPositionY.name, &fgVertexPositionY.value);
    tree->Branch(fgVertexPositionZ.name, &fgVertexPositionZ.value);
    tree->Branch(fgParticleName.name, const_cast<char*>(fgParticleName.value.Data()), "Particle/C");
    tree->Branch(fgTrackID.name, &fgTrackID.value);
}

void OrbitalDetectorHit::ReadBranches(TTree* tree) {
    DataModel::Hit::OrbitalDetectorHit::ReadBranches(tree);
    tree->SetBranchAddress(fgVertexTime.name, &fgVertexTime.value);
    tree->SetBranchAddress(fgVertexPositionX.name, &fgVertexPositionX.value);
    tree->SetBranchAddress(fgVertexPositionY.name, &fgVertexPositionY.value);
    tree->SetBranchAddress(fgVertexPositionZ.name, &fgVertexPositionZ.value);
    tree->SetBranchAddress(fgParticleName.name, &fgParticleName.value);
    tree->SetBranchAddress(fgTrackID.name, &fgTrackID.value);
}