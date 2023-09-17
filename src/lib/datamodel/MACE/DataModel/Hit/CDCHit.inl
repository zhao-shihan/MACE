namespace MACE::DataModel::inline Hit {

inline void CDCHit::FillAllBranchSocket() const& {
    fCellID.FillBranchSocket();
    fDriftDistance.FillBranchSocket();
    fTime.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
