#include "Core/DataModel/Hit/VertexDetectorHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket VertexDetectorHit::fgHitTime("hitTime", 0);
Vector2FBranchSocket VertexDetectorHit::fgHitPosition("hitPos", {"x", "y"}, {0, 0});
Vector2FBranchSocket VertexDetectorHit::fgHitPositionVariance("hitPosVar", {"x", "y"}, {0, 0});

VertexDetectorHit::VertexDetectorHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fHitPosition(fgHitPosition.GetValue<Double_t>()),
    fHitPositionVariance(fgHitPositionVariance.GetValue<Double_t>()) {}

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

void VertexDetectorHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgHitPosition.SetValue(fHitPosition);
    fgHitPositionVariance.SetValue(fHitPositionVariance);
}

} // namespace MACE::Core::DataModel::Hit
