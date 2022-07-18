namespace MACE::Core::DataModel::BranchSocket {

template<IsClass AClass>
template<typename... Args>
ClassBranchSocket<AClass>::ClassBranchSocket(const TString& branchName, Args&&... args) :
    IBranchSocket<AClass>(branchName),
    fObject(new AClass(std::forward<Args>(args)...)) {}

template<IsClass AClass>
ClassBranchSocket<AClass>::~ClassBranchSocket() noexcept {
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
