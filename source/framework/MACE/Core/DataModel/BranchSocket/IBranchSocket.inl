namespace MACE::Core::DataModel::BranchSocket {

template<typename T, bool PassByReference>
IBranchSocket<T, PassByReference>::IBranchSocket(const TString& branchName) :
    NonMoveableBase(),
    fBranchName(branchName) {}

} // namespace MACE::Core::DataModel::BranchSocket
