#include "MACE/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::DataModel {

template<>
MCPSimHit::Entry::MCEventID::BranchSocket MCPSimHit::Entry::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
MCPSimHit::Entry::MCTrackID::BranchSocket MCPSimHit::Entry::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
MCPSimHit::Entry::PDGCode::BranchSocket MCPSimHit::Entry::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
MCPSimHit::Entry::KineticEnergy::BranchSocket MCPSimHit::Entry::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Entry::Momentum::BranchSocket MCPSimHit::Entry::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Entry::VertexKineticEnergy::BranchSocket MCPSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
MCPSimHit::Entry::VertexMomentum::BranchSocket MCPSimHit::Entry::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void MCPSimHit::CreateAllBranch(TTree& tree) {
    MCPHit::CreateAllBranch(tree);
    Entry::MCEventID::CreateBranch(tree);
    Entry::MCTrackID::CreateBranch(tree);
    Entry::PDGCode::CreateBranch(tree);
    Entry::KineticEnergy::CreateBranch(tree);
    Entry::Momentum::CreateBranch(tree);
    Entry::VertexTime::CreateBranch(tree);
    Entry::VertexPosition::CreateBranch(tree);
    Entry::VertexKineticEnergy::CreateBranch(tree);
    Entry::VertexMomentum::CreateBranch(tree);
}

void MCPSimHit::ConnectToAllBranch(TTree& tree) {
    MCPHit::ConnectToAllBranch(tree);
    Entry::MCEventID::ConnectToBranch(tree);
    Entry::MCTrackID::ConnectToBranch(tree);
    Entry::PDGCode::ConnectToBranch(tree);
    Entry::KineticEnergy::ConnectToBranch(tree);
    Entry::Momentum::ConnectToBranch(tree);
    Entry::VertexTime::ConnectToBranch(tree);
    Entry::VertexPosition::ConnectToBranch(tree);
    Entry::VertexKineticEnergy::ConnectToBranch(tree);
    Entry::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
