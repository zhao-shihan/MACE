namespace MACE::DataModel::inline Hit {

inline void EMCalHit::FillAllBranchSocket() const& {
    fTime.FillBranchSocket();
    fEnergyDeposition.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
