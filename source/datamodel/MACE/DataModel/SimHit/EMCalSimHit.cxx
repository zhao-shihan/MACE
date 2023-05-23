#include "MACE/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::DataModel {

template<>
EMCalSimHit::Entry::MCEventID::BranchSocket EMCalSimHit::Entry::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
EMCalSimHit::Entry::MCTrackID::BranchSocket EMCalSimHit::Entry::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
EMCalSimHit::Entry::PDGCode::BranchSocket EMCalSimHit::Entry::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
EMCalSimHit::Entry::Position::BranchSocket EMCalSimHit::Entry::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Entry::Momentum::BranchSocket EMCalSimHit::Entry::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Entry::VertexTime::BranchSocket EMCalSimHit::Entry::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
EMCalSimHit::Entry::VertexPosition::BranchSocket EMCalSimHit::Entry::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Entry::VertexKineticEnergy::BranchSocket EMCalSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
EMCalSimHit::Entry::VertexMomentum::BranchSocket EMCalSimHit::Entry::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void EMCalSimHit::CreateAllBranch(TTree& tree) {
    EMCalHit::CreateAllBranch(tree);
    Entry::MCEventID::CreateBranch(tree);
    Entry::MCTrackID::CreateBranch(tree);
    Entry::PDGCode::CreateBranch(tree);
    Entry::Position::CreateBranch(tree);
    Entry::Momentum::CreateBranch(tree);
    Entry::VertexTime::CreateBranch(tree);
    Entry::VertexPosition::CreateBranch(tree);
    Entry::VertexKineticEnergy::CreateBranch(tree);
    Entry::VertexMomentum::CreateBranch(tree);
}

void EMCalSimHit::ConnectToAllBranch(TTree& tree) {
    EMCalHit::ConnectToAllBranch(tree);
    Entry::MCEventID::ConnectToBranch(tree);
    Entry::MCTrackID::ConnectToBranch(tree);
    Entry::PDGCode::ConnectToBranch(tree);
    Entry::Position::ConnectToBranch(tree);
    Entry::Momentum::ConnectToBranch(tree);
    Entry::VertexTime::ConnectToBranch(tree);
    Entry::VertexPosition::ConnectToBranch(tree);
    Entry::VertexKineticEnergy::ConnectToBranch(tree);
    Entry::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
