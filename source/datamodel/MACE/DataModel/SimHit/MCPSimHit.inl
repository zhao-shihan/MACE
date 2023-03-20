namespace MACE::DataModel::inline SimHit {

inline MCPSimHit::MCPSimHit() noexcept :
    MCPHit(),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fParticle(fgParticle.Value()) {}

inline void MCPSimHit::FillBranchSockets() const noexcept {
    MCPHit::FillBranchSockets();
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
    fgVertexTime.Value(fVertexTime);
    fgVertexPosition.Value(fVertexPosition);
    fgParticle.Value(fParticle);
}

} // namespace MACE::DataModel::inline SimHit
