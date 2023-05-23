#include "MACE/DataModel/Hit/MCPHit.hxx"

namespace MACE::DataModel {

template<>
MCPHit::Entry::Time::BranchSocket MCPHit::Entry::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};
template<>
MCPHit::Entry::Position::BranchSocket MCPHit::Entry::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position", {0, 0}}; // clang-format on

inline namespace Hit {

void MCPHit::CreateAllBranch(TTree& tree) {
    Entry::Time::CreateBranch(tree);
    Entry::Position::CreateBranch(tree);
}

void MCPHit::ConnectToAllBranch(TTree& tree) {
    Entry::Time::ConnectToBranch(tree);
    Entry::Position::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
