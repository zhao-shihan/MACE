namespace MACE::DataModel::inline Hit {

inline MCPHit::MCPHit() noexcept :
    fHitTime(fgHitTime.Value()),
    fHitPosition(fgHitPosition.Value<double>()) {}

inline void MCPHit::FillBranchSockets() const noexcept {
    fgHitTime.Value(fHitTime);
    fgHitPosition.Value(fHitPosition);
}

} // namespace MACE::DataModel::inline Hit
