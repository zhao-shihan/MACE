#include "MACE/DataModel/Hit/EMCalHit.hxx"

namespace MACE::DataModel {

template<>
EMCalHit::Entry::HitTime::BranchSocket EMCalHit::Entry::HitTime::Base::fgBranchSocket = {"t", 0};
template<>
EMCalHit::Entry::Energy::BranchSocket EMCalHit::Entry::Energy::Base::fgBranchSocket = {"E", 0};

inline namespace Hit {

void EMCalHit::CreateBranches(TTree& tree) {
    decltype(fHitTime)::CreateBranch(tree);
    decltype(fEnergy)::CreateBranch(tree);
}

void EMCalHit::ConnectToBranches(TTree& tree) {
    decltype(fHitTime)::ConnectToBranch(tree);
    decltype(fEnergy)::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
