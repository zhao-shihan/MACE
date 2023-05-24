#include "MACE/DataModel/Hit/MCPHit.hxx"

namespace MACE::DataModel {

template<>
MCPHit::Field::Time::BranchSocket MCPHit::Field::Time::Base::fgBranchSocket =
    {"t", "Hitting Time", 0};
template<>
MCPHit::Field::Position::BranchSocket MCPHit::Field::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position", {0, 0}}; // clang-format on

inline namespace Hit {

void MCPHit::CreateAllBranch(TTree& tree) {
    Field::Time::CreateBranch(tree);
    Field::Position::CreateBranch(tree);
}

void MCPHit::ConnectToAllBranch(TTree& tree) {
    Field::Time::ConnectToBranch(tree);
    Field::Position::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
