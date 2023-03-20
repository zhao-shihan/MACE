namespace MACE::DataModel::inline Hit {

inline CDCHit::CDCHit() noexcept :
    fCellID(fgCellID.Value()),
    fDriftDistance(fgDriftDistance.Value()),
    fHitTime(fgHitTime.Value()) {}

inline void CDCHit::FillBranchSockets() const noexcept {
    fgCellID.Value(fCellID);
    fgDriftDistance.Value(fDriftDistance);
    fgHitTime.Value(fHitTime);
}

} // namespace MACE::DataModel::inline Hit
