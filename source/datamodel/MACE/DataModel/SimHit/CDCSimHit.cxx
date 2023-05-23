#include "MACE/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::DataModel {

template<>
CDCSimHit::Entry::MCEventID::BranchSocket CDCSimHit::Entry::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
CDCSimHit::Entry::MCTrackID::BranchSocket CDCSimHit::Entry::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
CDCSimHit::Entry::PDGCode::BranchSocket CDCSimHit::Entry::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimHit::Entry::KineticEnergy::BranchSocket CDCSimHit::Entry::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Entry::Momentum::BranchSocket CDCSimHit::Entry::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Entry::VertexTime::BranchSocket CDCSimHit::Entry::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
CDCSimHit::Entry::VertexPosition::BranchSocket CDCSimHit::Entry::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Entry::VertexKineticEnergy::BranchSocket CDCSimHit::Entry::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Entry::VertexMomentum::BranchSocket CDCSimHit::Entry::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void CDCSimHit::CreateAllBranch(TTree& tree) {
    CDCHit::CreateAllBranch(tree);
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

void CDCSimHit::ConnectToAllBranch(TTree& tree) {
    CDCHit::ConnectToAllBranch(tree);
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
