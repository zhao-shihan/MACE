#include "SimG4/Hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

MACE::DataModel::Core::Column<TString> CalorimeterHit::fgParticleName = { "Particle", "" };
MACE::DataModel::Core::Column<Int_t> CalorimeterHit::fgTrackID = { "TrackID", -1 };

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::CalorimeterHitAllocator = nullptr;

CalorimeterHit::CalorimeterHit() noexcept :
    G4VHit(),
    DataModel::Hit::CalorimeterHit(),
    fParticleName(fgParticleName.value.Data()),
    fTrackID(fgTrackID.value) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::CalorimeterHit(static_cast<const DataModel::Hit::CalorimeterHit&>(hit)),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::CalorimeterHit(static_cast<DataModel::Hit::CalorimeterHit&&>(hit)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    G4VHit::operator=(static_cast<const G4VHit&>(hit));
    DataModel::Hit::CalorimeterHit::operator=(static_cast<const DataModel::Hit::CalorimeterHit&>(hit));
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    G4VHit::operator=(static_cast<G4VHit&&>(hit));
    DataModel::Hit::CalorimeterHit::operator=(static_cast<DataModel::Hit::CalorimeterHit&&>(hit));
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void CalorimeterHit::CreateBranches(TTree* tree) {
    DataModel::Hit::CalorimeterHit::CreateBranches(tree);
    tree->Branch(fgParticleName.name, const_cast<char*>(fgParticleName.value.Data()), "Particle/C");
    tree->Branch(fgTrackID.name, &fgTrackID.value);
}

void CalorimeterHit::ReadBranches(TTree* tree) {
    DataModel::Hit::CalorimeterHit::ReadBranches(tree);
    tree->Branch(fgParticleName.name, &fgParticleName.value);
    tree->Branch(fgTrackID.name, &fgTrackID.value);
}