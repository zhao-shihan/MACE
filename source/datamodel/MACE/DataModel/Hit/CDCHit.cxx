#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel {

template<>
CDCHit::Column::CellID::BranchSocket CDCHit::Column::CellID::Base::fgBranchSocket =
    {"cellID", "Hitting Cell ID", -1};
template<>
CDCHit::Column::DriftDistance::BranchSocket CDCHit::Column::DriftDistance::Base::fgBranchSocket =
    {"d", "Drift Distance", 0};
template<>
CDCHit::Column::Time::BranchSocket CDCHit::Column::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};

inline namespace Hit {

void CDCHit::CreateAllBranch(TTree& tree) {
    Column::CellID::CreateBranch(tree);
    Column::DriftDistance::CreateBranch(tree);
    Column::Time::CreateBranch(tree);
}

void CDCHit::ConnectToAllBranch(TTree& tree) {
    Column::CellID::ConnectToBranch(tree);
    Column::DriftDistance::ConnectToBranch(tree);
    Column::Time::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
