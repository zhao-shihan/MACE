namespace MACE::DataModel::inline SimTrack {

void CDCPhysicsSimTrack::FillAllBranchSocket() const& {
    CDCPhysicsTrack::FillAllBranchSocket();
    CDCSimTrackBase::FillAllBranchSocket();
    fVertexPositionTruth.FillBranchSocket();
    fVertexKineticEnergyTruth.FillBranchSocket();
    fVertexMomentumTruth.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimTrack
