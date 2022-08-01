namespace MACE::Core::DataModel::BranchSocket {

template<IsROOTFundamental AROOTFundamental>
FundamentalBranchSocket<AROOTFundamental>::FundamentalBranchSocket(const TString& branchName, AROOTFundamental defaultValue) :
    IBranchSocket<AROOTFundamental>(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
