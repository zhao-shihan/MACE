namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t, int Size>
VectorBranchSocket<Fund_t, Size>::VectorBranchSocket(const TString& branchName, const std::array<TString, Size>& leafList, const std::array<Fund_t, Size>& defaultValues) :
    IBranchSocket<Eigen::Vector<Fund_t, Size>>(branchName),
    fLeafList("") {
    // Construct leaf list
    fLeafList.Append(leafList[0]);
    fLeafList.Append('/');
    fLeafList.Append(GetBranchTypeName<Fund_t>());
    for (int i = 1; i < Size; ++i) {
        fLeafList.Append(':');
        fLeafList.Append(leafList[i]);
    }
    // Initialize vector
    for (int i = 1; i < Size; ++i) {
        fVector[i] = defaultValues[i];
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
