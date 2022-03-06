#include "DataModel/Hit/VertexDetectorHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket                VertexDetectorHit::fgHitTime("hitT", 0);
Vector2FBranchSocket         VertexDetectorHit::fgHitPosition("hitPos", 0, 0);
Vector2FBranchSocket VertexDetectorHit::fgHitPositionVariance("varHitPos", 0, 0);

VertexDetectorHit::VertexDetectorHit() noexcept :
    Base(),
    fHitTime(fgHitTime.Value()),
    fHitPosition(fgHitPosition.Value()),
    fHitPositionVariance(fgHitPositionVariance.Value()) {}

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
