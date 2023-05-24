#include "MACE/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::DataModel {

template<>
CDCSimHit::Field::MCEventID::BranchSocket CDCSimHit::Field::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
CDCSimHit::Field::MCTrackID::BranchSocket CDCSimHit::Field::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
CDCSimHit::Field::PDGCode::BranchSocket CDCSimHit::Field::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimHit::Field::KineticEnergy::BranchSocket CDCSimHit::Field::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Field::Momentum::BranchSocket CDCSimHit::Field::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Field::VertexTime::BranchSocket CDCSimHit::Field::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
CDCSimHit::Field::VertexPosition::BranchSocket CDCSimHit::Field::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Field::VertexKineticEnergy::BranchSocket CDCSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Field::VertexMomentum::BranchSocket CDCSimHit::Field::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void CDCSimHit::CreateAllBranch(TTree& tree) {
    CDCHit::CreateAllBranch(tree);
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

void CDCSimHit::ConnectToAllBranch(TTree& tree) {
    CDCHit::ConnectToAllBranch(tree);
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
