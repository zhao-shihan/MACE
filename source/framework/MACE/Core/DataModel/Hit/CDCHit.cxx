#include "MACE/Core/DataModel/Hit/CDCHit.hxx"

namespace MACE::Core::DataModel::Hit {

BranchSocket::DoubleBranchSocket CDCHit::fgHitTime("hitTime", 0);
BranchSocket::FloatBranchSocket CDCHit::fgDriftDistance("drift", 0);
BranchSocket::IntBranchSocket CDCHit::fgCellID("cellID", -1);

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

} // namespace MACE::Core::DataModel::Hit
