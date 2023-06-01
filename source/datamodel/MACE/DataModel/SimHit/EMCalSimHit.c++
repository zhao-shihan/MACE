#include "MACE/DataModel/SimHit/EMCalSimHit.h++"

namespace MACE::DataModel {

template<>
EMCalSimHit::Column::MCEventID::BranchSocket EMCalSimHit::Column::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
EMCalSimHit::Column::MCTrackID::BranchSocket EMCalSimHit::Column::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
EMCalSimHit::Column::PDGCode::BranchSocket EMCalSimHit::Column::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
EMCalSimHit::Column::Position::BranchSocket EMCalSimHit::Column::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Column::Momentum::BranchSocket EMCalSimHit::Column::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Column::VertexTime::BranchSocket EMCalSimHit::Column::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
EMCalSimHit::Column::VertexPosition::BranchSocket EMCalSimHit::Column::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Column::VertexKineticEnergy::BranchSocket EMCalSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
EMCalSimHit::Column::VertexMomentum::BranchSocket EMCalSimHit::Column::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void EMCalSimHit::CreateAllBranch(TTree& tree) {
    EMCalHit::CreateAllBranch(tree);
    Column::MCEventID::CreateBranch(tree);
    Column::MCTrackID::CreateBranch(tree);
    Column::PDGCode::CreateBranch(tree);
    Column::Position::CreateBranch(tree);
    Column::Momentum::CreateBranch(tree);
    Column::VertexTime::CreateBranch(tree);
    Column::VertexPosition::CreateBranch(tree);
    Column::VertexKineticEnergy::CreateBranch(tree);
    Column::VertexMomentum::CreateBranch(tree);
}

void EMCalSimHit::ConnectToAllBranch(TTree& tree) {
    EMCalHit::ConnectToAllBranch(tree);
    Column::MCEventID::ConnectToBranch(tree);
    Column::MCTrackID::ConnectToBranch(tree);
    Column::PDGCode::ConnectToBranch(tree);
    Column::Position::ConnectToBranch(tree);
    Column::Momentum::ConnectToBranch(tree);
    Column::VertexTime::ConnectToBranch(tree);
    Column::VertexPosition::ConnectToBranch(tree);
    Column::VertexKineticEnergy::ConnectToBranch(tree);
    Column::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
