namespace MACE::DataModel::inline Hit {

inline void EMCalHit::FillBranchSockets() const {
    fHitTime.FillBranchSocket();
    fEnergy.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
