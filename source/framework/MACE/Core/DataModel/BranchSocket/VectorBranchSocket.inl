namespace MACE::Core::DataModel::BranchSocket {

template<Concept::ArithmeticExcludeBoolChar T, int N>
VectorBranchSocket<T, N>::VectorBranchSocket(const std::string& branchName, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValues) :
    BranchSocketBase<VectorBranchSocket<T, N>, Eigen34::Vector<T, N>>(branchName),
    fLeafList(LeafListInitializer(leafNames)),
    fVector() {
    // Initialize vector
    for (int i = 0; i < N; ++i) {
        fVector[i] = defaultValues[i];
    }
}

template<Concept::ArithmeticExcludeBoolChar T, int N>
std::string VectorBranchSocket<T, N>::LeafListInitializer(const std::array<std::string, N>& leafNames) {
    std::string leafList;
    leafList.append(leafNames[0]).append(Utility::ROOTUtil::LeafType<T>().Suffix());
    for (int i = 1; i < N; ++i) {
        leafList.append(":").append(leafNames[i]);
    }
    return leafList;
}

} // namespace MACE::Core::DataModel::BranchSocket
