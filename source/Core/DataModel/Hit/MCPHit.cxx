#include "Core/DataModel/Hit/MCPHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket MCPHit::fgHitTime("hitTime", 0);
Vector2FBranchSocket MCPHit::fgHitPosition("hitPos", {"x", "y"}, {0, 0});
Vector2FBranchSocket MCPHit::fgHitPositionVariance("hitPosVar", {"x", "y"}, {0, 0});

MCPHit::MCPHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fHitPosition(fgHitPosition.GetValue<Double_t>()),
    fHitPositionVariance(fgHitPositionVariance.GetValue<Double_t>()) {}

void MCPHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgHitPosition.CreateBranch(tree);
    fgHitPositionVariance.CreateBranch(tree);
}

void MCPHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgHitPosition.ConnectToBranch(tree);
    fgHitPositionVariance.ConnectToBranch(tree);
}

void MCPHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgHitPosition.SetValue(fHitPosition);
    fgHitPositionVariance.SetValue(fHitPositionVariance);
}

} // namespace MACE::Core::DataModel::Hit
