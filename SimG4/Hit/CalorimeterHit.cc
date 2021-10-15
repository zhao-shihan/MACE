#include "SimG4/Hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

const char* CalorimeterHit::persistParticleName = "";
Int_t CalorimeterHit::persistTrackID = -1;

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::CalorimeterHitAllocator = nullptr;

CalorimeterHit::CalorimeterHit() noexcept :
    G4VHit(),
    DataModel::Hit::CalorimeterHit(),
    fParticleName(nullptr),
    fTrackID(-1) {}

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
    tree->Branch("Particle", const_cast<char*>(persistParticleName), "Particle/C");
    tree->Branch("TrackID", &persistTrackID);
}

void CalorimeterHit::FillBranches() noexcept {
    DataModel::Hit::CalorimeterHit::FillBranches();
    persistParticleName = fParticleName.Data();
    persistTrackID = fTrackID;
}