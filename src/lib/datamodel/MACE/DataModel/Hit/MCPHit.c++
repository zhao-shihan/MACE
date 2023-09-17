#include "MACE/DataModel/Hit/MCPHit.h++"

namespace MACE::DataModel {

template<>
MCPHit::Column::Time::BranchSocket MCPHit::Column::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};
template<>
MCPHit::Column::Position::BranchSocket MCPHit::Column::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position", {0, 0}}; // clang-format on

inline namespace Hit {

void MCPHit::CreateAllBranch(TTree& tree) {
    Column::Time::CreateBranch(tree);
    Column::Position::CreateBranch(tree);
}

void MCPHit::ConnectToAllBranch(TTree& tree) {
    Column::Time::ConnectToBranch(tree);
    Column::Position::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
