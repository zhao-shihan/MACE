namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental AROOTFundamental, int ASize>
VectorBranchSocket<AROOTFundamental, ASize>::VectorBranchSocket(const TString& branchName, const std::array<TString, ASize>& leafNames, const std::array<AROOTFundamental, ASize>& defaultValues) :
    IBranchSocket<Eigen::Vector<AROOTFundamental, ASize>>(branchName),
    fLeafList(""),
    fVector() {
    // Construct leaf list
    fLeafList.Append(leafNames[0]);
    fLeafList.Append('/');
    fLeafList.Append(GetBranchTypeName<AROOTFundamental>());
    for (int i = 1; i < ASize; ++i) {
        fLeafList.Append(':');
        fLeafList.Append(leafNames[i]);
    }
    // Initialize vector
    for (int i = 0; i < ASize; ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
