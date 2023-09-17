namespace MACE::DataModel::inline SimTrack {

void CDCHelixSimTrack::FillAllBranchSocket() const& {
    CDCHelixTrack::FillAllBranchSocket();
    CDCSimTrackBase::FillAllBranchSocket();
    fCenterTruth.FillBranchSocket();
    fRadiusTruth.FillBranchSocket();
    fVertexZTruth.FillBranchSocket();
    fThetaTruth.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimTrack
