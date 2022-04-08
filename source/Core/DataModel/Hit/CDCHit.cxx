#include "Core/DataModel/Hit/CDCHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket CDCHit::fgHitTime("hitTime", 0);
FloatBranchSocket CDCHit::fgDriftDistance("drift", 0);
FloatBranchSocket CDCHit::fgHitPositionZ("hitPosZ", 0);
FloatBranchSocket CDCHit::fgDriftDistanceVariance("driftVar", 0);
FloatBranchSocket CDCHit::fgHitPositionZVariance("hitPosZVar", 0);
Vector2FBranchSocket CDCHit::fgWirePosition("wirePos", {"x", "y"}, {0, 0});
Vector3FBranchSocket CDCHit::fgWireDirection("wireDir", {"x", "y", "z"}, {0, 0, 0});
IntBranchSocket CDCHit::fgCellID("cellID", -1);
IntBranchSocket CDCHit::fgLayerID("layerID", -1);

CDCHit::CDCHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fDriftDistance(fgDriftDistance.GetValue()),
    fHitPositionZ(fgHitPositionZ.GetValue()),
    fDriftDistanceVariance(fgDriftDistanceVariance.GetValue()),
    fHitPositionZVariance(fgHitPositionZVariance.GetValue()),
    fWirePosition(fgWirePosition.GetValue<Double_t>()),
    fWireDirection(fgWireDirection.GetValue<Double_t>()),
    fCellID(fgCellID.GetValue()),
    fLayerID(fgLayerID.GetValue()) {}

void CDCHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgDriftDistance.CreateBranch(tree);
    fgHitPositionZ.CreateBranch(tree);
    fgDriftDistanceVariance.CreateBranch(tree);
    fgHitPositionZVariance.CreateBranch(tree);
    fgWirePosition.CreateBranch(tree);
    fgWireDirection.CreateBranch(tree);
    fgCellID.CreateBranch(tree);
    fgLayerID.CreateBranch(tree);
}

void CDCHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgDriftDistance.ConnectToBranch(tree);
    fgHitPositionZ.ConnectToBranch(tree);
    fgDriftDistanceVariance.ConnectToBranch(tree);
    fgHitPositionZVariance.ConnectToBranch(tree);
    fgWirePosition.ConnectToBranch(tree);
    fgWireDirection.ConnectToBranch(tree);
    fgCellID.ConnectToBranch(tree);
    fgLayerID.ConnectToBranch(tree);
}

void CDCHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgDriftDistance.SetValue(fDriftDistance);
    fgHitPositionZ.SetValue(fHitPositionZ);
    fgDriftDistanceVariance.SetValue(fDriftDistanceVariance);
    fgHitPositionZVariance.SetValue(fHitPositionZVariance);
    fgWirePosition.SetValue(fWirePosition);
    fgWireDirection.SetValue(fWireDirection);
    fgCellID.SetValue(fCellID);
    fgLayerID.SetValue(fLayerID);
}

} // namespace MACE::Core::DataModel::Hit
