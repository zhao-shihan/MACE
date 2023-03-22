namespace MACE::DataModel::inline SimHit {

inline void EMCalSimHit::FillBranchSockets() const {
    EMCalHit::FillBranchSockets();
    fG4EventID.FillBranchSocket();
    fG4TrackID.FillBranchSocket();
    fParticle.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
