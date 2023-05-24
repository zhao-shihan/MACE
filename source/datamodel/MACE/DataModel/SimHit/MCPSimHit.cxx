#include "MACE/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::DataModel {

template<>
MCPSimHit::Field::MCEventID::BranchSocket MCPSimHit::Field::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
MCPSimHit::Field::MCTrackID::BranchSocket MCPSimHit::Field::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
MCPSimHit::Field::PDGCode::BranchSocket MCPSimHit::Field::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
MCPSimHit::Field::KineticEnergy::BranchSocket MCPSimHit::Field::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Field::Momentum::BranchSocket MCPSimHit::Field::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Field::VertexTime::BranchSocket MCPSimHit::Field::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
MCPSimHit::Field::VertexPosition::BranchSocket MCPSimHit::Field::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Field::VertexKineticEnergy::BranchSocket MCPSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Field::VertexMomentum::BranchSocket MCPSimHit::Field::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void MCPSimHit::CreateAllBranch(TTree& tree) {
    MCPHit::CreateAllBranch(tree);
    Field::MCEventID::CreateBranch(tree);
    Field::MCTrackID::CreateBranch(tree);
    Field::PDGCode::CreateBranch(tree);
    Field::KineticEnergy::CreateBranch(tree);
    Field::Momentum::CreateBranch(tree);
    Field::VertexTime::CreateBranch(tree);
    Field::VertexPosition::CreateBranch(tree);
    Field::VertexKineticEnergy::CreateBranch(tree);
    Field::VertexMomentum::CreateBranch(tree);
}

void MCPSimHit::ConnectToAllBranch(TTree& tree) {
    MCPHit::ConnectToAllBranch(tree);
    Field::MCEventID::ConnectToBranch(tree);
    Field::MCTrackID::ConnectToBranch(tree);
    Field::PDGCode::ConnectToBranch(tree);
    Field::KineticEnergy::ConnectToBranch(tree);
    Field::Momentum::ConnectToBranch(tree);
    Field::VertexTime::ConnectToBranch(tree);
    Field::VertexPosition::ConnectToBranch(tree);
    Field::VertexKineticEnergy::ConnectToBranch(tree);
    Field::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
