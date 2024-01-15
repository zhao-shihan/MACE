namespace MACE::DataModel::inline Track {

void CDCPhysicsTrack::FillAllBranchSocket() const& {
    CDCTrackBase::FillAllBranchSocket();
    fVertexPosition.FillBranchSocket();
    fVertexKineticEnergy.FillBranchSocket();
    fVertexMomentum.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Track
