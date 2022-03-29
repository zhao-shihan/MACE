#include "Core/DataModel/Hit/SpectrometerHit.hxx"

namespace MACE::Core::DataModel::Hit {

DoubleBranchSocket SpectrometerHit::fgHitTime("hitTime", 0);
FloatBranchSocket SpectrometerHit::fgDriftDistance("drift", 0);
FloatBranchSocket SpectrometerHit::fgHitPositionZ("hitPosZ", 0);
FloatBranchSocket SpectrometerHit::fgDriftDistanceVariance("driftVar", 0);
FloatBranchSocket SpectrometerHit::fgHitPositionZVariance("hitPosZVar", 0);
IntBranchSocket SpectrometerHit::fgCellID("cellID", -1);
IntBranchSocket SpectrometerHit::fgLayerID("layerID", -1);

SpectrometerHit::SpectrometerHit() noexcept :
    ITransientData(),
    fHitTime(fgHitTime.GetValue()),
    fDriftDistance(fgDriftDistance.GetValue()),
    fHitPositionZ(fgHitPositionZ.GetValue()),
    fDriftDistanceVariance(fgDriftDistanceVariance.GetValue()),
    fHitPositionZVariance(fgHitPositionZVariance.GetValue()),
    fCellID(fgCellID.GetValue()),
    fLayerID(fgLayerID.GetValue()) {}

void SpectrometerHit::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgHitTime.CreateBranch(tree);
    fgDriftDistance.CreateBranch(tree);
    fgHitPositionZ.CreateBranch(tree);
    fgDriftDistanceVariance.CreateBranch(tree);
    fgHitPositionZVariance.CreateBranch(tree);
    fgCellID.CreateBranch(tree);
    fgLayerID.CreateBranch(tree);
}

void SpectrometerHit::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgHitTime.ConnectToBranch(tree);
    fgDriftDistance.ConnectToBranch(tree);
    fgHitPositionZ.ConnectToBranch(tree);
    fgDriftDistanceVariance.ConnectToBranch(tree);
    fgHitPositionZVariance.ConnectToBranch(tree);
    fgCellID.ConnectToBranch(tree);
    fgLayerID.ConnectToBranch(tree);
}

void SpectrometerHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgDriftDistance.SetValue(fDriftDistance);
    fgHitPositionZ.SetValue(fHitPositionZ);
    fgDriftDistanceVariance.SetValue(fDriftDistanceVariance);
    fgHitPositionZVariance.SetValue(fHitPositionZVariance);
    fgCellID.SetValue(fCellID);
    fgLayerID.SetValue(fLayerID);
}

} // namespace MACE::Core::DataModel::Hit
