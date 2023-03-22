namespace MACE::DataModel::inline Hit {

inline void MCPHit::FillBranchSockets() const {
    fHitTime.FillBranchSocket();
    fHitPosition.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
