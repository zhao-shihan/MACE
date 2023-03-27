namespace MACE::DataModel::inline SimHit {

inline void EMCalSimHit::FillBranchSockets() const {
    EMCalHit::FillBranchSockets();
    fG4EventID.FillBranchSocket();
    fG4TrackID.FillBranchSocket();
    fPDGCode.FillBranchSocket();
    fMomentum.FillBranchSocket();
    fVertexTime.FillBranchSocket();
    fVertexPosition.FillBranchSocket();
    fVertexEnergy.FillBranchSocket();
    fVertexMomentum.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
