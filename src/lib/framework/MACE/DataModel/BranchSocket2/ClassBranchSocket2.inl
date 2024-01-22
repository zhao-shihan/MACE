namespace MACE::DataModel::inline BranchSocket {

template<typename AClass>
template<typename... Args>
ClassBranchSocket2<AClass>::ClassBranchSocket2(std::string name, std::string title, std::tuple<Args&&...> argTuple) :
    BranchSocketBase2<ClassBranchSocket2<AClass>, AClass>(std::move(name), std::move(title)),
    fObject(std::apply(
        [](auto&&... args) {
            return new AClass(std::forward<decltype(args)>(args)...);
        },
        argTuple)) {}

template<typename AClass>
ClassBranchSocket2<AClass>::~ClassBranchSocket2() {
    delete fObject;
}

} // namespace MACE::DataModel::inline BranchSocket
