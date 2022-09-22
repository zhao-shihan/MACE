#include "MACE/Core/DataModel/Hit/CDCHit.hxx"

namespace MACE::Core::DataModel::Hit {

BranchSocket::DoubleBranchSocket CDCHit::fgHitTime("hitTime", 0);
BranchSocket::FloatBranchSocket CDCHit::fgDriftDistance("drift", 0);
BranchSocket::FloatBranchSocket CDCHit::fgHitPositionZ("hitPosZ", 0);
BranchSocket::FloatBranchSocket CDCHit::fgDriftDistanceVariance("driftVar", 0);
BranchSocket::FloatBranchSocket CDCHit::fgHitPositionZVariance("hitPosZVar", 0);
BranchSocket::Vector2FBranchSocket CDCHit::fgWirePosition("wirePos", {"x", "y"}, {0, 0});
BranchSocket::Vector3FBranchSocket CDCHit::fgWireDirection("wireDir", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::IntBranchSocket CDCHit::fgCellID("cellID", -1);
BranchSocket::IntBranchSocket CDCHit::fgLayerID("layerID", -1);

CDCHit::CDCHit() noexcept :
    fHitTime(fgHitTime.Value()),
    fDriftDistance(fgDriftDistance.Value()),
    fHitPositionZ(fgHitPositionZ.Value()),
    fDriftDistanceVariance(fgDriftDistanceVariance.Value()),
    fHitPositionZVariance(fgHitPositionZVariance.Value()),
    fWirePosition(fgWirePosition.Value<double>()),
    fWireDirection(fgWireDirection.Value<double>()),
    fCellID(fgCellID.Value()),
    fLayerID(fgLayerID.Value()) {}

void CDCHit::FillBranchSockets() const noexcept {
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

void CDCHit::CreateBranches(TTree& tree) {
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

} // namespace MACE::Core::DataModel::Hit
