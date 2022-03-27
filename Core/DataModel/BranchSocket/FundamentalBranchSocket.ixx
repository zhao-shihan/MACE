namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental Fund_t>
FundamentalBranchSocket<Fund_t>::FundamentalBranchSocket(const TString& branchName, Fund_t defaultValue) :
    IBranchSocket<Fund_t>(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
