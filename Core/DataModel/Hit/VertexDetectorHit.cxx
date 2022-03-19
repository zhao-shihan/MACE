#include "DataModel/Hit/VertexDetectorHit.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket               VertexDetectorHit::fgHitTime("hitTime", 0);
Vector2FBranchSocket         VertexDetectorHit::fgHitPosition("hitPos", { "x", "y" }, { 0, 0 });
Vector2FBranchSocket VertexDetectorHit::fgHitPositionVariance("hitPosVar", { "x", "y" }, { 0, 0 });

VertexDetectorHit::VertexDetectorHit() noexcept :
    Base(),
    fHitTime(fgHitTime.GetValue()),
    fHitPosition(fgHitPosition.GetValue()),
    fHitPositionVariance(fgHitPositionVariance.GetValue()) {}

void VertexDetectorHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgHitPosition.CreateBranch(tree);
    fgHitPositionVariance.CreateBranch(tree);
}

void VertexDetectorHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgHitPosition.ConnectToBranch(tree);
    fgHitPositionVariance.ConnectToBranch(tree);
}
