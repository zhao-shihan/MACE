namespace MACE::DataModel::inline BranchSocket {

template<class ADerived, typename T>
BranchSocketBase2<ADerived, T>::BranchSocketBase2(std::string name, std::string title) :
    NonMoveableBase(),
    fName(std::move(name)),
    fTitle(std::move(title)) {
    static_assert(BranchSocket2<ADerived, T>);
}

} // namespace MACE::DataModel
