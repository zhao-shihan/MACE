namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental ROOTFundamentalT, int SizeV>
VectorBranchSocket<ROOTFundamentalT, SizeV>::VectorBranchSocket(const TString& branchName, const std::array<TString, SizeV>& leafNames, const std::array<ROOTFundamentalT, SizeV>& defaultValues) :
    IBranchSocket<Eigen::Vector<ROOTFundamentalT, SizeV>>(branchName),
    fLeafList(""),
    fVector() {
    // Construct leaf list
    fLeafList.Append(leafNames[0]);
    fLeafList.Append('/');
    fLeafList.Append(GetBranchTypeName<ROOTFundamentalT>());
    for (int i = 1; i < SizeV; ++i) {
        fLeafList.Append(':');
        fLeafList.Append(leafNames[i]);
    }
    // Initialize vector
    for (int i = 1; i < SizeV; ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
