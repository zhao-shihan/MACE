namespace MACE::Core::DataModel::BranchSocket {

template<Concept::Arithmetic T, int N>
VectorBranchSocket<T, N>::VectorBranchSocket(const std::string& branchName, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValues) :
    BranchSocketBase<VectorBranchSocket<T, N>, std::array<T, N>>(branchName),
    fLeafList(
        [&leafNames] {
            std::string leafList;
            leafList.append(leafNames[0]).append(std::string{'/', Utility::ROOTUtil::LeafTypeCode<T>()});
            for (int i = 1; i < N; ++i) {
                leafList.append(":").append(leafNames[i]);
            }
            return leafList;
        }()),
    fVector() {
    // Initialize vector
    for (int i = 0; i < N; ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
