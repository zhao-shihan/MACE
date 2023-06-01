#include "MACE/DataModel/SimHit/MCPSimHit.h++"

namespace MACE::DataModel {

template<>
MCPSimHit::Column::MCEventID::BranchSocket MCPSimHit::Column::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
MCPSimHit::Column::MCTrackID::BranchSocket MCPSimHit::Column::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
MCPSimHit::Column::PDGCode::BranchSocket MCPSimHit::Column::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
MCPSimHit::Column::KineticEnergy::BranchSocket MCPSimHit::Column::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Column::Momentum::BranchSocket MCPSimHit::Column::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Column::VertexTime::BranchSocket MCPSimHit::Column::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
MCPSimHit::Column::VertexPosition::BranchSocket MCPSimHit::Column::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Column::VertexKineticEnergy::BranchSocket MCPSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Column::VertexMomentum::BranchSocket MCPSimHit::Column::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void MCPSimHit::CreateAllBranch(TTree& tree) {
    MCPHit::CreateAllBranch(tree);
    Column::MCEventID::CreateBranch(tree);
    Column::MCTrackID::CreateBranch(tree);
    Column::PDGCode::CreateBranch(tree);
    Column::KineticEnergy::CreateBranch(tree);
    Column::Momentum::CreateBranch(tree);
    Column::VertexTime::CreateBranch(tree);
    Column::VertexPosition::CreateBranch(tree);
    Column::VertexKineticEnergy::CreateBranch(tree);
    Column::VertexMomentum::CreateBranch(tree);
}

void MCPSimHit::ConnectToAllBranch(TTree& tree) {
    MCPHit::ConnectToAllBranch(tree);
    Column::MCEventID::ConnectToBranch(tree);
    Column::MCTrackID::ConnectToBranch(tree);
    Column::PDGCode::ConnectToBranch(tree);
    Column::KineticEnergy::ConnectToBranch(tree);
    Column::Momentum::ConnectToBranch(tree);
    Column::VertexTime::ConnectToBranch(tree);
    Column::VertexPosition::ConnectToBranch(tree);
    Column::VertexKineticEnergy::ConnectToBranch(tree);
    Column::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
