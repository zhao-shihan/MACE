#include "MACE/Core/DataModel/Hit/CDCHit.hxx"

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
    fHitTime(fgHitTime.Value()),
    fDriftDistance(fgDriftDistance.Value()),
    fHitPositionZ(fgHitPositionZ.Value()),
    fDriftDistanceVariance(fgDriftDistanceVariance.Value()),
    fHitPositionZVariance(fgHitPositionZVariance.Value()),
    fWirePosition(fgWirePosition.Value<double>()),
    fWireDirection(fgWireDirection.Value<double>()),
    fCellID(fgCellID.Value()),
    fLayerID(fgLayerID.Value()) {}

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
    fgHitTime.Value(fHitTime);
    fgDriftDistance.Value(fDriftDistance);
    fgHitPositionZ.Value(fHitPositionZ);
    fgDriftDistanceVariance.Value(fDriftDistanceVariance);
    fgHitPositionZVariance.Value(fHitPositionZVariance);
    fgWirePosition.Value(fWirePosition);
    fgWireDirection.Value(fWireDirection);
    fgCellID.Value(fCellID);
    fgLayerID.Value(fLayerID);
}

} // namespace MACE::Core::DataModel::Hit
