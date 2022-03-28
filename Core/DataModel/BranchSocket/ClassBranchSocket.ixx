namespace MACE::Core::DataModel::BranchSocket {

template<IsClass Class_t>
template<typename... Args>
ClassBranchSocket<Class_t>::ClassBranchSocket(const TString& branchName, Args&&... args) :
    IBranchSocket<Class_t>(branchName),
    fObject(new Class_t(std::forward<Args>(args)...)) {}

template<IsClass Class_t>
ClassBranchSocket<Class_t>::~ClassBranchSocket() noexcept {
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
