template<typename Fund_t>
MACE::DataModel::FundamentalBranchSocket<Fund_t>::FundamentalBranchSocket(const char* branchName, Fund_t defaultValue) :
    MACE::DataModel::Interface::BranchSocket<Fund_t>(),
    fBranchName(branchName),
    fValue(defaultValue) {}
