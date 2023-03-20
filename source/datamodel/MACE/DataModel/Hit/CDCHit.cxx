#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel::inline Hit {

DoubleBranchSocket CDCHit::fgHitTime("hitTime", 0);
FloatBranchSocket CDCHit::fgDriftDistance("drift", 0);
IntBranchSocket CDCHit::fgCellID("cellID", -1);

void CDCHit::CreateBranches(TTree& tree) {
    fgCellID.CreateBranch(tree);
    fgDriftDistance.CreateBranch(tree);
    fgHitTime.CreateBranch(tree);
}

void CDCHit::ConnectToBranches(TTree& tree) {
    fgCellID.ConnectToBranch(tree);
    fgDriftDistance.ConnectToBranch(tree);
    fgHitTime.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::inline Hit
