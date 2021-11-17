#include "SimG4/Hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

MACE::DataModel::Column<Int_t> CalorimeterHit::fgPDGCode = { "PDGCode", 0 };
MACE::DataModel::Column<Int_t> CalorimeterHit::fgTrackID = { "TrackID", -1 };

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::CalorimeterHitAllocator = nullptr;

CalorimeterHit::CalorimeterHit() noexcept :
    G4VHit(),
    DataModel::Hit::CalorimeterHit(),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::Hit::CalorimeterHit(static_cast<const DataModel::Hit::CalorimeterHit&>(hit)),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::Hit::CalorimeterHit(static_cast<DataModel::Hit::CalorimeterHit&&>(hit)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    G4VHit::operator=(static_cast<const G4VHit&>(hit));
    DataModel::Hit::CalorimeterHit::operator=(static_cast<const DataModel::Hit::CalorimeterHit&>(hit));
    fPDGCode = hit.fPDGCode;
    fTrackID = hit.fTrackID;
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    G4VHit::operator=(static_cast<G4VHit&&>(hit));
    DataModel::Hit::CalorimeterHit::operator=(static_cast<DataModel::Hit::CalorimeterHit&&>(hit));
    fPDGCode = std::move(hit.fPDGCode);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

void CalorimeterHit::CreateBranches(TTree* tree) {
    DataModel::Hit::CalorimeterHit::CreateBranches(tree);
    tree->Branch(fgPDGCode.name, &fgPDGCode.value);
    tree->Branch(fgTrackID.name, &fgTrackID.value);
}

void CalorimeterHit::ReadBranches(TTree* tree) {
    DataModel::Hit::CalorimeterHit::ReadBranches(tree);
    tree->SetBranchAddress(fgPDGCode.name, &fgPDGCode.value);
    tree->SetBranchAddress(fgTrackID.name, &fgTrackID.value);
}