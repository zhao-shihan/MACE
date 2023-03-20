namespace MACE::DataModel::inline SimHit {

inline CDCSimHit::CDCSimHit() noexcept :
    CDCHit(),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()),
    fEnergy(fgEnergy.Value()),
    fMomentum(fgMomentum.Value<double>()),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fParticle(fgParticle.Value()) {}

inline void CDCSimHit::FillBranchSockets() const noexcept {
    CDCHit::FillBranchSockets();
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
    fgEnergy.Value(fEnergy);
    fgMomentum.Value(fMomentum);
    fgVertexTime.Value(fVertexTime);
    fgVertexPosition.Value(fVertexPosition);
    fgVertexEnergy.Value(fVertexEnergy);
    fgVertexMomentum.Value(fVertexMomentum);
    fgParticle.Value(fParticle);
}

} // namespace MACE::DataModel::inline SimHit
