#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket                 SpectrometerHit::fgHitTime("hitT", 0);
FloatBranchSocket           SpectrometerHit::fgDriftDistance("drift", 0);
FloatBranchSocket            SpectrometerHit::fgHitPositionZ("hitZ", 0);
FloatBranchSocket   SpectrometerHit::fgDriftDistanceVariance("varDrift", 0);
FloatBranchSocket    SpectrometerHit::fgHitPositionZVariance("varHitZ", 0);
IntBranchSocket                    SpectrometerHit::fgCellID("cellID", -1);
IntBranchSocket                   SpectrometerHit::fgLayerID("layerID", -1);
Vector2FBranchSocket         SpectrometerHit::fgWirePosition("wirePos", 0, 0);

SpectrometerHit::SpectrometerHit() noexcept :
    Base(),
    fHitTime(fgHitTime.Value()),
    fDriftDistance(fgDriftDistance.Value()),
    fHitPositionZ(fgHitPositionZ.Value()),
    fDriftDistanceVariance(fgDriftDistanceVariance.Value()),
    fHitPositionZVariance(fgHitPositionZVariance.Value()),
    fCellID(fgCellID.Value()),
    fLayerID(fgLayerID.Value()),
    fWirePosition(fgWirePosition.Value()) {}

void SpectrometerHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgDriftDistance.CreateBranch(tree);
    fgHitPositionZ.CreateBranch(tree);
    fgDriftDistanceVariance.CreateBranch(tree);
    fgHitPositionZVariance.CreateBranch(tree);
    fgCellID.CreateBranch(tree);
    fgLayerID.CreateBranch(tree);
    fgWirePosition.CreateBranch(tree);
}

void SpectrometerHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgDriftDistance.ConnectToBranch(tree);
    fgHitPositionZ.ConnectToBranch(tree);
    fgDriftDistanceVariance.ConnectToBranch(tree);
    fgHitPositionZVariance.ConnectToBranch(tree);
    fgCellID.ConnectToBranch(tree);
    fgLayerID.ConnectToBranch(tree);
    fgWirePosition.ConnectToBranch(tree);
}
