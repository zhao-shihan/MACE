template<typename Class_t>
template<typename... Args>
MACE::DataModel::ClassBranchSocket<Class_t>::
ClassBranchSocket(const char* branchName, Args&&... args) :
    MACE::DataModel::Interface::BranchSocket<Class_t>(),
    fBranchName(branchName),
    fObject(new Class_t(std::forward<Args>(args)...)) {}

template<typename Class_t>
MACE::DataModel::ClassBranchSocket<Class_t>::
~ClassBranchSocket() noexcept {
    delete fObject;
}
