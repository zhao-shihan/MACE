namespace MACE::DataModel::inline Hit {

inline void EMCHit::FillAllBranchSocket() const& {
    fTime.FillBranchSocket();
    fEnergyDeposition.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
