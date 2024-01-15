namespace MACE::DataModel::inline SimHit {

inline void CDCSimHit::FillAllBranchSocket() const& {
    CDCHit::FillAllBranchSocket();
    fMCEventID.FillBranchSocket();
    fMCTrackID.FillBranchSocket();
    fPDGCode.FillBranchSocket();
    fKineticEnergy.FillBranchSocket();
    fMomentum.FillBranchSocket();
    fVertexTime.FillBranchSocket();
    fVertexPosition.FillBranchSocket();
    fVertexKineticEnergy.FillBranchSocket();
    fVertexMomentum.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
