#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

Column<Int_t> CalorimeterSimHit::fgPDGCode = { "PDGCode", 0 };
Column<Int_t> CalorimeterSimHit::fgTrackID = { "TrackID", -1 };

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fPDGCode(fgPDGCode.value),
    fTrackID(fgTrackID.value) {}

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
