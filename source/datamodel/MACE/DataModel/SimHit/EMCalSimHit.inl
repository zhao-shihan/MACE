namespace MACE::DataModel::SimHit {

inline EMCalSimHit::EMCalSimHit() noexcept :
    EMCalHit(),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()),
    fParticle(fgParticle.Value()) {}

inline void EMCalSimHit::FillBranchSockets() const noexcept {
    EMCalHit::FillBranchSockets();
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
    fgParticle.Value(fParticle);
}

} // namespace MACE::DataModel::SimHit
