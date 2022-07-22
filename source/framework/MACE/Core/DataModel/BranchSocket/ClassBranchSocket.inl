namespace MACE::Core::DataModel::BranchSocket {

template<class AClass> // clang-format off
    requires std::assignable_from<AClass, AClass>
template<typename... Args> // clang-format on
ClassBranchSocket<AClass>::ClassBranchSocket(const TString& branchName, std::tuple<Args&&...> argTuple) :
    IBranchSocket<AClass>(branchName),
    fObject(std::apply(
        []<typename... Ts>(Ts&&... args) {
            return new AClass(std::forward<Ts>(args)...);
        },
        argTuple)) {}

template<class AClass> // clang-format off
    requires std::assignable_from<AClass, AClass>
ClassBranchSocket<AClass>::~ClassBranchSocket() { // clang-format on
    delete fObject;
}

} // namespace MACE::Core::DataModel::BranchSocket
