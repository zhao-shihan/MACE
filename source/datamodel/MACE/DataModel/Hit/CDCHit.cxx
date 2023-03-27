#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel {

template<>
CDCHit::Entry::CellID::BranchSocket CDCHit::Entry::CellID::Base::fgBranchSocket = {"cellID", -1};
template<>
CDCHit::Entry::DriftDistance::BranchSocket CDCHit::Entry::DriftDistance::Base::fgBranchSocket = {"d", 0};
template<>
CDCHit::Entry::HitTime::BranchSocket CDCHit::Entry::HitTime::Base::fgBranchSocket = {"t", 0};

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
