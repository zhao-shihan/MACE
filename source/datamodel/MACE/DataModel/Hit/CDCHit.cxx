#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel {

template<>
CDCHit::Entry::CellID::BranchSocket CDCHit::Entry::CellID::Base::fgBranchSocket =
    {"cellID", "Hitting Cell ID", -1};
template<>
CDCHit::Entry::DriftDistance::BranchSocket CDCHit::Entry::DriftDistance::Base::fgBranchSocket =
    {"d", "Drift Distance", 0};
template<>
CDCHit::Entry::Time::BranchSocket CDCHit::Entry::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};

inline namespace Hit {

void CDCHit::CreateAllBranch(TTree& tree) {
    Entry::CellID::CreateBranch(tree);
    Entry::DriftDistance::CreateBranch(tree);
    Entry::Time::CreateBranch(tree);
}

void CDCHit::ConnectToAllBranch(TTree& tree) {
    Entry::CellID::ConnectToBranch(tree);
    Entry::DriftDistance::ConnectToBranch(tree);
    Entry::Time::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
