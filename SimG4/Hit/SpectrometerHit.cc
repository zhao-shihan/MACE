#include "SimG4/Hit/SpectrometerHit.hh"

using namespace MACE::SimG4::Hit;

MACE::DataModel::Core::Column<Float_t> SpectrometerHit::fgVertexTime = { "VertexT", 0.0f };
MACE::DataModel::Core::Column<Float_t> SpectrometerHit::fgVertexPositionX = { "VertexX", 0.0f };
MACE::DataModel::Core::Column<Float_t> SpectrometerHit::fgVertexPositionY = { "VertexY", 0.0f };
MACE::DataModel::Core::Column<Float_t> SpectrometerHit::fgVertexPositionZ = { "VertexZ", 0.0f };
MACE::DataModel::Core::Column<TString> SpectrometerHit::fgParticleName = { "Particle", "" };
MACE::DataModel::Core::Column<Int_t> SpectrometerHit::fgTrackID = { "TrackID", -1 };

G4Allocator<SpectrometerHit>* MACE::SimG4::Hit::SpectrometerHitAllocator = nullptr;

SpectrometerHit::SpectrometerHit() noexcept :
    G4VHit(),
    DataModel::Hit::SpectrometerHit(),
    fVertexTime(fgVertexTime.value),
    fVertexPosition(fgVertexPositionX.value, fgVertexPositionY.value, fgVertexPositionZ.value),
    fParticleName(fgParticleName.value.Data()),
    fTrackID(fgTrackID.value) {}

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
    tree->Branch(fgVertexTime.name, &fgVertexTime.value);
    tree->Branch(fgVertexPositionX.name, &fgVertexPositionX.value);
    tree->Branch(fgVertexPositionY.name, &fgVertexPositionY.value);
    tree->Branch(fgVertexPositionZ.name, &fgVertexPositionZ.value);
    tree->Branch(fgParticleName.name, const_cast<char*>(fgParticleName.value.Data()), "Particle/C");
    tree->Branch(fgTrackID.name, &fgTrackID.value);
}

void SpectrometerHit::ReadBranches(TTree* tree) {
    DataModel::Hit::SpectrometerHit::ReadBranches(tree);
    tree->SetBranchAddress(fgVertexTime.name, &fgVertexTime.value);
    tree->SetBranchAddress(fgVertexPositionX.name, &fgVertexPositionX.value);
    tree->SetBranchAddress(fgVertexPositionY.name, &fgVertexPositionY.value);
    tree->SetBranchAddress(fgVertexPositionZ.name, &fgVertexPositionZ.value);
    tree->SetBranchAddress(fgParticleName.name, &fgParticleName.value);
    tree->SetBranchAddress(fgTrackID.name, &fgTrackID.value);
}