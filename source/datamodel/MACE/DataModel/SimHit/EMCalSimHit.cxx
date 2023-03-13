#include "MACE/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::DataModel::SimHit {

BranchSocket::ShortStringBranchSocket EMCalSimHit::fgParticle("particle", "");
BranchSocket::IntBranchSocket EMCalSimHit::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket EMCalSimHit::fgG4TrackID("g4TrackID", -1);

void EMCalSimHit::CreateBranches(TTree& tree) {
    EMCalHit::CreateBranches(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
}

void EMCalSimHit::ConnectToBranches(TTree& tree) {
    EMCalHit::ConnectToBranches(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::SimHit
