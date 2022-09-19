namespace MACE::Core::DataModel::BranchSocket {

template<Concept::ROOTFundamental T>
FundamentalBranchSocket<T>::FundamentalBranchSocket(const std::string& branchName, T defaultValue) :
    BranchSocketBase<FundamentalBranchSocket<T>, T>(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
