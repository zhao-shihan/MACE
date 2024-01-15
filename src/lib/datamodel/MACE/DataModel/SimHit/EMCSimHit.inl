namespace MACE::DataModel::inline SimHit {

inline void EMCSimHit::FillAllBranchSocket() const& {
    EMCHit::FillAllBranchSocket();
    fMCEventID.FillBranchSocket();
    fMCTrackID.FillBranchSocket();
    fPDGCode.FillBranchSocket();
    fPosition.FillBranchSocket();
    fMomentum.FillBranchSocket();
    fVertexTime.FillBranchSocket();
    fVertexPosition.FillBranchSocket();
    fVertexKineticEnergy.FillBranchSocket();
    fVertexMomentum.FillBranchSocket();
}

} // namespace MACE::DataModel::inline SimHit
