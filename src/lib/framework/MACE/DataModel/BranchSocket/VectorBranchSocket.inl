namespace MACE::DataModel::inline BranchSocket {

template<Concept::Arithmetic T, std::size_t N>
VectorBranchSocket<T, N>::VectorBranchSocket(const std::string& branchName, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValues) :
    BranchSocketBase<VectorBranchSocket<T, N>, std::array<T, N>>(branchName),
    fLeafList(
        [&leafNames] {
            std::string leafList;
            leafList.append(leafNames[0]).append(std::string{'/', ROOTX::LeafTypeCode<T>()});
            for (gsl::index i = 1; i < stdx::to_signed(N); ++i) {
                leafList.append(":").append(leafNames[i]);
            }
            return leafList;
        }()),
    fVector() {
    // Initialize vector
    for (gsl::index i = 0; i < stdx::to_signed(N); ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::DataModel::inline BranchSocket
