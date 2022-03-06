#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

IntBranchSocket CalorimeterSimHit::fgPDGCode("pdgCode", std::numeric_limits<Int_t>::max());
IntBranchSocket CalorimeterSimHit::fgEventID("evtID", -1);
IntBranchSocket CalorimeterSimHit::fgTrackID("trkID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    Base(),
    fPDGCode(fgPDGCode.Value()),
    fEventID(fgEventID.Value()),
    fTrackID(fgTrackID.Value()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgEventID.BranchName(), fgEventID.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgEventID.BranchName(), fgEventID.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
