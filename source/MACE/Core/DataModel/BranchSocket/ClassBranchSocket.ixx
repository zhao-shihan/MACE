namespace MACE::Core::DataModel::BranchSocket {

template<IsClass ClassT>
template<typename... Args>
ClassBranchSocket<ClassT>::ClassBranchSocket(const TString& branchName, Args&&... args) :
    IBranchSocket<ClassT>(branchName),
    fObject(new ClassT(std::forward<Args>(args)...)) {}

template<IsClass ClassT>
ClassBranchSocket<ClassT>::~ClassBranchSocket() noexcept {
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
