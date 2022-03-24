#include "DataModel/SimHit/CalorimeterSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

ShortStringBranchSocket CalorimeterSimHit::fgParticleName("particle", "");
IntBranchSocket CalorimeterSimHit::fgEventID("eventID", -1);
IntBranchSocket CalorimeterSimHit::fgTrackID("trackID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    CalorimeterHit(),
    fParticleName(fgParticleName.GetValue()),
    fEventID(fgEventID.GetValue()),
    fTrackID(fgTrackID.GetValue()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    CalorimeterHit::CreateBranches(tree);
    fgParticleName.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    CalorimeterHit::ConnectToBranches(tree);
    fgParticleName.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimHit
