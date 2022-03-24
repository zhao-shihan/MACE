namespace MACE::Core::DataModel::BranchSocket {

template<typename Fund_t>
FundamentalBranchSocket<Fund_t>::FundamentalBranchSocket(const char* branchName, Fund_t defaultValue) :
    IBranchSocket<Fund_t>(),
    fBranchName(branchName),
    fValue(defaultValue) {}

} // namespace MACE::Core::DataModel::BranchSocket
