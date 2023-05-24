#include "MACE/DataModel/Hit/CDCHit.hxx"

namespace MACE::DataModel {

template<>
CDCHit::Field::CellID::BranchSocket CDCHit::Field::CellID::Base::fgBranchSocket =
    {"cellID", "Hitting Cell ID", -1};
template<>
CDCHit::Field::DriftDistance::BranchSocket CDCHit::Field::DriftDistance::Base::fgBranchSocket =
    {"d", "Drift Distance", 0};
template<>
CDCHit::Field::Time::BranchSocket CDCHit::Field::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};

inline namespace Hit {

void CDCHit::CreateAllBranch(TTree& tree) {
    Field::CellID::CreateBranch(tree);
    Field::DriftDistance::CreateBranch(tree);
    Field::Time::CreateBranch(tree);
}

void CDCHit::ConnectToAllBranch(TTree& tree) {
    Field::CellID::ConnectToBranch(tree);
    Field::DriftDistance::ConnectToBranch(tree);
    Field::Time::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
