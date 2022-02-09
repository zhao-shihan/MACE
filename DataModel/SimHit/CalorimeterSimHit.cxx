#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

MACE::DataModel::Column<Int_t> CalorimeterSimHit::fgPDGCode = { "PDGCode", 0 };
MACE::DataModel::Column<Int_t> CalorimeterSimHit::fgTrackID = { "TrackID", -1 };

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    DataModel::CalorimeterHit(),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

CalorimeterSimHit::CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept :
    DataModel::CalorimeterHit(static_cast<const DataModel::CalorimeterHit&>(hit)),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

CalorimeterSimHit::CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept :
    DataModel::CalorimeterHit(static_cast<DataModel::CalorimeterHit&&>(hit)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

CalorimeterSimHit& CalorimeterSimHit::operator=(const CalorimeterSimHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        DataModel::CalorimeterHit::operator=(static_cast<const DataModel::CalorimeterHit&>(hit));
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

CalorimeterSimHit& CalorimeterSimHit::operator=(CalorimeterSimHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        DataModel::CalorimeterHit::operator=(static_cast<DataModel::CalorimeterHit&&>(hit));
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void CalorimeterSimHit::CreateBranches(TTree* tree) {
    DataModel::CalorimeterHit::CreateBranches(tree);
    tree->Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void CalorimeterSimHit::ReadBranches(TTree* tree) {
    DataModel::CalorimeterHit::ReadBranches(tree);
    tree->SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree->SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}