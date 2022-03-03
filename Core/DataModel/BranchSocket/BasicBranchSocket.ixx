template<typename Arith_t>
MACE::DataModel::BasicBranchSocket<Arith_t>::BasicBranchSocket(const char* branchName, Arith_t defaultValue) :
    MACE::DataModel::Interface::BranchSocket<Arith_t, Arith_t*>(branchName),
    fValue(defaultValue) {}
