namespace MACE::DataModel::inline Hit {

inline EMCalHit::EMCalHit() noexcept :
    fHitTime(fgHitTime.Value()),
    fEnergy(fgEnergy.Value()) {}

inline void EMCalHit::FillBranchSockets() const noexcept {
    fgHitTime.Value(fHitTime);
    fgEnergy.Value(fEnergy);
}

} // namespace MACE::DataModel::inline Hit
