namespace MACE::Core::DataModel::BranchSocket {

template<class AClass> // clang-format off
    requires std::assignable_from<AClass, AClass>
template<typename... Args> // clang-format on
ClassBranchSocket<AClass>::ClassBranchSocket(const std::string& branchName, std::tuple<Args&&...> argTuple) :
    BranchSocketBase<ClassBranchSocket<AClass>, AClass>(branchName),
    fObject(std::apply(
        [](auto&&... args) {
            return new AClass(std::forward<decltype(args)>(args)...);
        },
        argTuple)) {}

template<class AClass> // clang-format off
    requires std::assignable_from<AClass, AClass>
ClassBranchSocket<AClass>::~ClassBranchSocket() { // clang-format on
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
