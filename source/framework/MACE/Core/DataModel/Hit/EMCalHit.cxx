#include "MACE/Core/DataModel/Hit/EMCalHit.hxx"

namespace MACE::Core::DataModel::Hit {

BranchSocket::DoubleBranchSocket EMCalHit::fgHitTime("hitTime", 0);
BranchSocket::FloatBranchSocket EMCalHit::fgEnergy("hitEne", 0);

void EMCalHit::CreateBranches(TTree& tree) {
    fgHitTime.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
}

void EMCalHit::ConnectToBranches(TTree& tree) {
    fgHitTime.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Hit
