namespace MACE::DataModel::inline Hit {

inline void MCPHit::FillAllBranchSocket() const& {
    fTime.FillBranchSocket();
    fPosition.FillBranchSocket();
}

} // namespace MACE::DataModel::inline Hit
