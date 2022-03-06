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
    tree.Branch(fgHitTime.BranchName(), fgHitTime.Address());
    tree.Branch(fgHitPosition.BranchName(), fgHitPosition.Address());
    tree.Branch(fgHitPositionVariance.BranchName(), fgHitPositionVariance.Address());
}

void VertexDetectorHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgHitTime.BranchName(), fgHitTime.Address());
    tree.SetBranchAddress(fgHitPosition.BranchName(), fgHitPosition.Address());
    tree.SetBranchAddress(fgHitPositionVariance.BranchName(), fgHitPositionVariance.Address());
}
