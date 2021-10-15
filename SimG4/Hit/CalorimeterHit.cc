#include "SimG4/Hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(CalorimeterHit, ParticleName, "");
MACE_DATA_MODEL_PERSISTIFIER_DEF(CalorimeterHit, TrackID, -1);

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::AllocatorOfCalorimeter = nullptr;

CalorimeterHit::CalorimeterHit() noexcept :
    G4VHit(),
    DataModel::Hit::CalorimeterHit(),
    fParticleName(nullptr),
    fTrackID(-1) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    G4VHit(hit),
    DataModel::Hit::CalorimeterHit(hit),
    fParticleName(hit.fParticleName),
    fTrackID(hit.fTrackID) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    G4VHit(std::move(hit)),
    DataModel::Hit::CalorimeterHit(std::move(hit)),
    fParticleName(std::move(hit.fParticleName)),
    fTrackID(std::move(hit.fTrackID)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    G4VHit::operator=(hit);
    DataModel::Hit::CalorimeterHit::operator=(hit);
    fParticleName = hit.fParticleName;
    fTrackID = hit.fTrackID;
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    G4VHit::operator=(std::move(hit));
    DataModel::Hit::CalorimeterHit::operator=(std::move(hit));
    fParticleName = std::move(hit.fParticleName);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void CalorimeterHit::CreateBranches(TTree* tree) {
    DataModel::Hit::CalorimeterHit::CreateBranches(tree);
    tree->Branch("ParticleName", const_cast<char*>(persistParticleName.Data()), "ParticleName/C");
    tree->Branch("TrackID", &persistTrackID);
}

void CalorimeterHit::FillBranches() {
    DataModel::Hit::CalorimeterHit::FillBranches();
    persistParticleName = fParticleName;
    persistTrackID = fTrackID;
}