#include "DataModel/Hit/VertexDetectorHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket                VertexDetectorHit::fgHitTime("HitT", 0);
Vector2FBranchSocket         VertexDetectorHit::fgHitPosition("HitPos", 0, 0);
Vector2FBranchSocket VertexDetectorHit::fgHitPositionVariance("HitPosVar", 0, 0);

VertexDetectorHit::VertexDetectorHit() noexcept :
    Data(),
    fHitTime(fgHitTime.Value()),
    fHitPosition(fgHitPosition.Value()),
    fHitPositionVariance(fgHitPositionVariance.Value()) {}

void VertexDetectorHit::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgHitTime.BranchName(), fgHitTime.Address());
    tree.Branch(fgHitPosition.BranchName(), fgHitPosition.Address());
    tree.Branch(fgHitPositionVariance.BranchName(), fgHitPositionVariance.Address());
}

void VertexDetectorHit::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgHitTime.BranchName(), fgHitTime.Address());
    tree.SetBranchAddress(fgHitPosition.BranchName(), fgHitPosition.Address());
    tree.SetBranchAddress(fgHitPositionVariance.BranchName(), fgHitPositionVariance.Address());
}
