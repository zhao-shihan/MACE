namespace MACE::DataModel {

template<class ADerived, typename T>
BranchSocketBase2<ADerived, T>::BranchSocketBase2(std::string name) :
    NonMoveableBase(),
    fName(std::move(name)) {
    static_assert(BranchSocketable2<ADerived, T>);
}

} // namespace MACE::DataModel
