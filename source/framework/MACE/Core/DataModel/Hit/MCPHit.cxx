#include "MACE/Core/DataModel/Hit/MCPHit.hxx"

namespace MACE::Core::DataModel::Hit {

BranchSocket::DoubleBranchSocket MCPHit::fgHitTime("hitTime", 0);
BranchSocket::Vector2FBranchSocket MCPHit::fgHitPosition("hitPos", {"x", "y"}, {0, 0});
BranchSocket::Vector2FBranchSocket MCPHit::fgHitPositionVariance("hitPosVar", {"x", "y"}, {0, 0});

MCPHit::MCPHit() noexcept :
    fHitTime(fgHitTime.Value()),
    fHitPosition(fgHitPosition.Value<double>()),
    fHitPositionVariance(fgHitPositionVariance.Value<double>()) {}

void MCPHit::FillBranchSockets() const noexcept {
    fgHitTime.Value(fHitTime);
    fgHitPosition.Value(fHitPosition);
    fgHitPositionVariance.Value(fHitPositionVariance);
}

void MCPHit::CreateBranches(TTree& tree) {
    fgHitTime.CreateBranch(tree);
    fgHitPosition.CreateBranch(tree);
    fgHitPositionVariance.CreateBranch(tree);
}

void MCPHit::ConnectToBranches(TTree& tree) {
    fgHitTime.ConnectToBranch(tree);
    fgHitPosition.ConnectToBranch(tree);
    fgHitPositionVariance.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Hit
