namespace MACE::DataModel {

template<class ADerived, typename T>
BranchSocketBase<ADerived, T>::BranchSocketBase(const std::string& branchName) :
    NonMoveableBase(),
    fBranchName(branchName) {
    static_assert(BranchSocketable<ADerived, T>);
}

} // namespace MACE::DataModel
