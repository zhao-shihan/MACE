namespace MACE::DataModel::inline BranchSocket {

template<class AClass>
template<typename... Args>
ClassBranchSocket2<AClass>::ClassBranchSocket2(std::string name, std::tuple<Args&&...> argTuple) :
    BranchSocketBase2<ClassBranchSocket2<AClass>, AClass>(std::move(name)),
    fObject(std::apply(
        [](auto&&... args) {
            return new AClass(std::forward<decltype(args)>(args)...);
        },
        argTuple)) {}

template<class AClass>
ClassBranchSocket2<AClass>::~ClassBranchSocket2() {
    delete fObject;
}

} // namespace MACE::DataModel::inline BranchSocket
