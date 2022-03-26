#include "DataModel/SimHit/CalorimeterSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

ShortStringBranchSocket CalorimeterSimHit::fgParticle("particle", "");
IntBranchSocket CalorimeterSimHit::fgEventID("eventID", -1);
IntBranchSocket CalorimeterSimHit::fgTrackID("trackID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fParticle(fgParticle.GetValue()),
    fEventID(fgEventID.GetValue()),
    fTrackID(fgTrackID.GetValue()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    CalorimeterHit::CreateBranches(tree);
    fgParticle.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    CalorimeterHit::ConnectToBranches(tree);
    fgParticle.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}

void CalorimeterSimHit::FillBranchSockets() const noexcept {
    CalorimeterHit::FillBranchSockets();
    fgParticle.SetValue(fParticle);
    fgEventID.SetValue(fEventID);
    fgTrackID.SetValue(fTrackID);
}

} // namespace MACE::Core::DataModel::SimHit
