namespace MACE::Core::DataModel::BranchSocket {

template<typename Class_t>
template<typename... Args>
ClassBranchSocket<Class_t>::ClassBranchSocket(const char* branchName, Args&&... args) :
    IBranchSocket<Class_t>(),
    fBranchName(branchName),
    fObject(new Class_t(std::forward<Args>(args)...)) {}

template<typename Class_t>
ClassBranchSocket<Class_t>::~ClassBranchSocket() noexcept {
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
