namespace MACE::DataModel::inline SimTrack {

void CDCSimTrackBase::FillAllBranchSocket() const& {
    fPDGCodeTruth.FillBranchSocket();
    fNHitTruth.FillBranchSocket();
    fVertexTimeTruth.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimTrack
