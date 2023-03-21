#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel {

template<>
IntEntry<CDCHit, 0, int>::BranchSocket IntEntry<CDCHit, 0, int>::Base::fgBranchSocket("cellID", -1);
template<>
FloatEntry<CDCHit, 1, double>::BranchSocket FloatEntry<CDCHit, 1, double>::Base::fgBranchSocket("drift", 0);
template<>
DoubleEntry<CDCHit, 2, double>::BranchSocket DoubleEntry<CDCHit, 2, double>::Base::fgBranchSocket("hitTime", 0);

inline namespace Hit {

void CDCHit::CreateBranches(TTree& tree) {
    decltype(fCellID)::CreateBranch(tree);
    decltype(fDriftDistance)::CreateBranch(tree);
    decltype(fHitTime)::CreateBranch(tree);
}

void CDCHit::ConnectToBranches(TTree& tree) {
    decltype(fCellID)::ConnectToBranch(tree);
    decltype(fDriftDistance)::ConnectToBranch(tree);
    decltype(fHitTime)::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
