#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

IntBranchSocket CalorimeterSimHit::fgPDGCode("PDGCode", std::numeric_limits<Int_t>::max());
IntBranchSocket CalorimeterSimHit::fgTrackID("TrackID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fPDGCode(fgPDGCode.Value()),
    fTrackID(fgTrackID.Value()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    CalorimeterHit::CreateBranches(tree);
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void CalorimeterSimHit::ReadBranches(TTree& tree) {
    CalorimeterHit::ReadBranches(tree);
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
