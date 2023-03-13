namespace MACE::DataModel::BranchSocket {

template<class AClass>
    requires std::assignable_from<AClass, AClass>
template<typename... Args>
ClassBranchSocket<AClass>::ClassBranchSocket(const std::string& branchName, std::tuple<Args&&...> argTuple) :
    BranchSocketBase<ClassBranchSocket<AClass>, AClass>(branchName),
    fObject(std::apply(
        [](auto&&... args) {
            return new AClass(std::forward<decltype(args)>(args)...);
        },
        argTuple)) {}

template<class AClass>
    requires std::assignable_from<AClass, AClass>
ClassBranchSocket<AClass>::~ClassBranchSocket() {
    delete fObject;
}

} // namespace MACE::DataModel::BranchSocket
