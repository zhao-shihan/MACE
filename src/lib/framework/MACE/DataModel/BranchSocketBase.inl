namespace MACE::DataModel {

template<class ADerived, typename T>
BranchSocketBase<ADerived, T>::BranchSocketBase(std::string branchName) :
    NonMoveableBase(),
    fBranchName(std::move(branchName)) {
    static_assert(BranchSocketable<ADerived, T>);
}

} // namespace MACE::DataModel
