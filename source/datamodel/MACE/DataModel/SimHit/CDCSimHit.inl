namespace MACE::DataModel::inline SimHit {

inline void CDCSimHit::FillBranchSockets() const {
    CDCHit::FillBranchSockets();
    fG4EventID.FillBranchSocket();
    fG4TrackID.FillBranchSocket();
    fEnergy.FillBranchSocket();
    fMomentum.FillBranchSocket();
    fVertexTime.FillBranchSocket();
    fVertexPosition.FillBranchSocket();
    fVertexEnergy.FillBranchSocket();
    fVertexMomentum.FillBranchSocket();
    fParticle.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
