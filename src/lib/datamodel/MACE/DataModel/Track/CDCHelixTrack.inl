namespace MACE::DataModel::inline Track {

void CDCHelixTrack::FillAllBranchSocket() const& {
    CDCTrackBase::FillAllBranchSocket();
    fCenter.FillBranchSocket();
    fRadius.FillBranchSocket();
    fVertexZ.FillBranchSocket();
    fTheta.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Track
