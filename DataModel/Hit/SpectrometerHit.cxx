#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket                 SpectrometerHit::fgHitTime("HitT", 0);
FloatBranchSocket           SpectrometerHit::fgDriftDistance("DriftD", 0);
FloatBranchSocket            SpectrometerHit::fgHitPositionZ("HitZ", 0);
FloatBranchSocket   SpectrometerHit::fgDriftDistanceVariance("DriftDVar", 0);
FloatBranchSocket    SpectrometerHit::fgHitPositionZVariance("HitZVar", 0);
IntBranchSocket                    SpectrometerHit::fgCellID("CellID", -1);
IntBranchSocket                   SpectrometerHit::fgLayerID("LayerID", -1);
Vector2FBranchSocket         SpectrometerHit::fgWirePosition("WirePos", 0, 0);

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
    tree.Branch(fgHitTime.BranchName(), fgHitTime.Address());
    tree.Branch(fgDriftDistance.BranchName(), fgDriftDistance.Address());
    tree.Branch(fgHitPositionZ.BranchName(), fgHitPositionZ.Address());
    tree.Branch(fgDriftDistanceVariance.BranchName(), fgDriftDistanceVariance.Address());
    tree.Branch(fgHitPositionZVariance.BranchName(), fgHitPositionZVariance.Address());
    tree.Branch(fgCellID.BranchName(), fgCellID.Address());
    tree.Branch(fgLayerID.BranchName(), fgLayerID.Address());
    tree.Branch(fgWirePosition.BranchName(), fgWirePosition.Address());
}

void SpectrometerHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgHitTime.BranchName(), fgHitTime.Address());
    tree.SetBranchAddress(fgDriftDistance.BranchName(), fgDriftDistance.Address());
    tree.SetBranchAddress(fgHitPositionZ.BranchName(), fgHitPositionZ.Address());
    tree.SetBranchAddress(fgDriftDistanceVariance.BranchName(), fgDriftDistanceVariance.Address());
    tree.SetBranchAddress(fgHitPositionZVariance.BranchName(), fgHitPositionZVariance.Address());
    tree.SetBranchAddress(fgCellID.BranchName(), fgCellID.Address());
    tree.SetBranchAddress(fgLayerID.BranchName(), fgLayerID.Address());
    tree.SetBranchAddress(fgWirePosition.BranchName(), fgWirePosition.Address());
}
