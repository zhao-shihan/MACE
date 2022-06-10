namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental ROOTFundamentalT>
FundamentalBranchSocket<ROOTFundamentalT>::FundamentalBranchSocket(const TString& branchName, ROOTFundamentalT defaultValue) :
    IBranchSocket<ROOTFundamentalT>(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
