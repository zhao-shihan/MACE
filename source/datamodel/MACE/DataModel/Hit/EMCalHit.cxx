#include "MACE/DataModel/Hit/EMCalHit.hxx"

namespace MACE::DataModel::inline Hit {

DoubleBranchSocket EMCalHit::fgHitTime("hitTime", 0);
FloatBranchSocket EMCalHit::fgEnergy("hitEne", 0);

void EMCalHit::CreateBranches(TTree& tree) {
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
}

void EMCalHit::ConnectToBranches(TTree& tree) {
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::inline Hit
