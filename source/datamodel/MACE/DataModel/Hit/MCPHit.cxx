#include "MACE/DataModel/Hit/MCPHit.hxx"

namespace MACE::DataModel {

template<>
MCPHit::Entry::HitTime::BranchSocket MCPHit::Entry::HitTime::Base::fgBranchSocket = {"t", 0};
template<> // clang-format off
MCPHit::Entry::HitPosition::BranchSocket MCPHit::Entry::HitPosition::Base::fgBranchSocket = {"x", {0, 0}}; // clang-format on

inline namespace Hit {

void MCPHit::CreateBranches(TTree& tree) {
    decltype(fHitTime)::CreateBranch(tree);
    decltype(fHitPosition)::CreateBranch(tree);
}

void MCPHit::ConnectToBranches(TTree& tree) {
    decltype(fHitTime)::ConnectToBranch(tree);
    decltype(fHitPosition)::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
