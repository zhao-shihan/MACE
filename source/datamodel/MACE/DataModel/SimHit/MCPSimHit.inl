namespace MACE::DataModel::inline SimHit {

inline void MCPSimHit::FillBranchSockets() const {
    MCPHit::FillBranchSockets();
    fG4EventID.FillBranchSocket();
    fG4TrackID.FillBranchSocket();
    fVertexTime.FillBranchSocket();
    fVertexPosition.FillBranchSocket();
    fParticle.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
