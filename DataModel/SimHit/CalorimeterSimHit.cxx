#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

Column<Int_t> CalorimeterSimHit::fgPDGCode = { "PDGCode", 0 };
Column<Int_t> CalorimeterSimHit::fgTrackID = { "TrackID", -1 };

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

CalorimeterSimHit::CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept :
    CalorimeterHit(static_cast<const CalorimeterHit&>(hit)),
    fPDGCode(hit.fPDGCode),
    fTrackID(hit.fTrackID) {}

CalorimeterSimHit::CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept :
    CalorimeterHit(static_cast<CalorimeterHit&&>(hit)),
    fPDGCode(std::move(hit.fPDGCode)),
    fTrackID(std::move(hit.fTrackID)) {}

CalorimeterSimHit& CalorimeterSimHit::operator=(const CalorimeterSimHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        CalorimeterHit::operator=(static_cast<const CalorimeterHit&>(hit));
        fPDGCode = hit.fPDGCode;
        fTrackID = hit.fTrackID;
    }
    return *this;
}

CalorimeterSimHit& CalorimeterSimHit::operator=(CalorimeterSimHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        CalorimeterHit::operator=(static_cast<CalorimeterHit&&>(hit));
        fPDGCode = std::move(hit.fPDGCode);
        fTrackID = std::move(hit.fTrackID);
    }
    return *this;
}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    CalorimeterHit::CreateBranches(tree);
    tree.Branch(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree.Branch(fgTrackID.name, std::addressof(fgTrackID.value));
}

void CalorimeterSimHit::ReadBranches(TTree& tree) {
    CalorimeterHit::ReadBranches(tree);
    tree.SetBranchAddress(fgPDGCode.name, std::addressof(fgPDGCode.value));
    tree.SetBranchAddress(fgTrackID.name, std::addressof(fgTrackID.value));
}