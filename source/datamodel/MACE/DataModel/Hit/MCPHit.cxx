#include "MACE/DataModel/Hit/MCPHit.hxx"

namespace MACE::DataModel::inline Hit {

DoubleBranchSocket MCPHit::fgHitTime("hitTime", 0);
Vector2FBranchSocket MCPHit::fgHitPosition("hitPos", {"x", "y"}, {0, 0});

void MCPHit::CreateBranches(TTree& tree) {
    fgHitTime.CreateBranch(tree);
    fgHitPosition.CreateBranch(tree);
}

void MCPHit::ConnectToBranches(TTree& tree) {
    fgHitTime.ConnectToBranch(tree);
    fgHitPosition.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::inline Hit
