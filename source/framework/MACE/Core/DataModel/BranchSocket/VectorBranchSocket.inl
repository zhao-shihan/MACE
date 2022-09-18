namespace MACE::Core::DataModel::BranchSocket {

template<ROOTFundamental T, int N>
VectorBranchSocket<T, N>::VectorBranchSocket(const TString& branchName, const std::array<TString, N>& leafNames, const std::array<T, N>& defaultValues) :
    IBranchSocket<Eigen34::Vector<T, N>>(branchName),
    fLeafList(""),
    fVector() {
    // Construct leaf list
    fLeafList.Append(leafNames[0]);
    fLeafList.Append('/');
    fLeafList.Append(LeafTypeCode<T>());
    for (int i = 1; i < N; ++i) {
        fLeafList.Append(':');
        fLeafList.Append(leafNames[i]);
    }
    // Initialize vector
    for (int i = 0; i < N; ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
