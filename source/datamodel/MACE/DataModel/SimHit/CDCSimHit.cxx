#include "MACE/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::DataModel {

template<>
CDCSimHit::Column::MCEventID::BranchSocket CDCSimHit::Column::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
CDCSimHit::Column::MCTrackID::BranchSocket CDCSimHit::Column::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
CDCSimHit::Column::PDGCode::BranchSocket CDCSimHit::Column::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimHit::Column::KineticEnergy::BranchSocket CDCSimHit::Column::KineticEnergy::Base::fgBranchSocket =
    {"Ek", "Hitting Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Column::Momentum::BranchSocket CDCSimHit::Column::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Column::VertexTime::BranchSocket CDCSimHit::Column::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
CDCSimHit::Column::VertexPosition::BranchSocket CDCSimHit::Column::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Column::VertexKineticEnergy::BranchSocket CDCSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
CDCSimHit::Column::VertexMomentum::BranchSocket CDCSimHit::Column::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void CDCSimHit::CreateAllBranch(TTree& tree) {
    CDCHit::CreateAllBranch(tree);
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

void CDCSimHit::ConnectToAllBranch(TTree& tree) {
    CDCHit::ConnectToAllBranch(tree);
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
