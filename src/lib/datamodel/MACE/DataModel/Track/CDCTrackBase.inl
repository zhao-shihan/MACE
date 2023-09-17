namespace MACE::DataModel::inline Track {

void CDCTrackBase::FillAllBranchSocket() const& {
    fPDGCode.FillBranchSocket();
    fNHit.FillBranchSocket();
    fChi2.FillBranchSocket();
    fVertexTime.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Track
