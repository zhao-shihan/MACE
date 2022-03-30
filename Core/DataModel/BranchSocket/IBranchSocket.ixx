namespace MACE::Core::DataModel::BranchSocket {

template<typename Type, bool UseReferenceInGetSet>
IBranchSocket<Type, UseReferenceInGetSet>::IBranchSocket(const TString& branchName) :
    fBranchName(branchName) {}

} // namespace MACE::Core::DataModel
