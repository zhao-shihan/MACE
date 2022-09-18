namespace MACE::Core::DataModel::BranchSocket {

template<ROOTFundamental T>
FundamentalBranchSocket<T>::FundamentalBranchSocket(const TString& branchName, T defaultValue) :
    IBranchSocket<T>(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
