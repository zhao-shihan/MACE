namespace MACE::DataModel::inline Hit {

inline void CDCHit::FillBranchSockets() const {
    fCellID.FillBranchSocket();
    fDriftDistance.FillBranchSocket();
    fHitTime.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
