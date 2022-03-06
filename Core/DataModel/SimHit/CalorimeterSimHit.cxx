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
    fgPDGCode.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgPDGCode.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
