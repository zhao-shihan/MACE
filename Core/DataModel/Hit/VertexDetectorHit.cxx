#include "DataModel/Hit/VertexDetectorHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket VertexDetectorHit::fgHitTime("hitTime", 0);
Vector2FBranchSocket VertexDetectorHit::fgHitPosition("hitPos", {"x", "y"}, {0, 0});
Vector2FBranchSocket VertexDetectorHit::fgHitPositionVariance("hitPosVar", {"x", "y"}, {0, 0});

VertexDetectorHit::VertexDetectorHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fHitPosition(fgHitPosition.GetValue()),
    fHitPositionVariance(fgHitPositionVariance.GetValue()) {}

void VertexDetectorHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgHitPosition.CreateBranch(tree);
    fgHitPositionVariance.CreateBranch(tree);
}

void VertexDetectorHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgHitPosition.ConnectToBranch(tree);
    fgHitPositionVariance.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Hit
