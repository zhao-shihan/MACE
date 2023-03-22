namespace MACE::DataModel::inline BranchSocket {

template<Concept::ROOTFundamental T, std::size_t N>
VectorBranchSocket2<T, N>::VectorBranchSocket2(std::string name, std::array<T, N> defaultValue) :
    BranchSocketBase2<VectorBranchSocket2<T, N>, std::array<T, N>>(std::move(name)),
    fVector(std::move(defaultValue)) {}

} // namespace MACE::DataModel::inline BranchSocket
