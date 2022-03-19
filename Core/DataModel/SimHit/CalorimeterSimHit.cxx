#include "DataModel/SimHit/CalorimeterSimHit.hxx"

using namespace MACE::DataModel;

ShortStringBranchSocket CalorimeterSimHit::fgParticleName("particle", "");
IntBranchSocket              CalorimeterSimHit::fgEventID("eventID", -1);
IntBranchSocket              CalorimeterSimHit::fgTrackID("trackID", -1);

CalorimeterSimHit::CalorimeterSimHit() noexcept :
    Base(),
    fParticleName(fgParticleName.GetValue()),
    fEventID(fgEventID.GetValue()),
    fTrackID(fgTrackID.GetValue()) {}

void CalorimeterSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgParticleName.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void CalorimeterSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgParticleName.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
