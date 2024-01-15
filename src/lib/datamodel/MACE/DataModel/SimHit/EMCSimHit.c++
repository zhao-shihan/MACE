#include "MACE/DataModel/SimHit/EMCSimHit.h++"

namespace MACE::DataModel {

template<>
EMCSimHit::Column::MCEventID::BranchSocket EMCSimHit::Column::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
EMCSimHit::Column::MCTrackID::BranchSocket EMCSimHit::Column::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
EMCSimHit::Column::PDGCode::BranchSocket EMCSimHit::Column::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
EMCSimHit::Column::Position::BranchSocket EMCSimHit::Column::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCSimHit::Column::Momentum::BranchSocket EMCSimHit::Column::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCSimHit::Column::VertexTime::BranchSocket EMCSimHit::Column::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
EMCSimHit::Column::VertexPosition::BranchSocket EMCSimHit::Column::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCSimHit::Column::VertexKineticEnergy::BranchSocket EMCSimHit::Column::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
EMCSimHit::Column::VertexMomentum::BranchSocket EMCSimHit::Column::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void EMCSimHit::CreateAllBranch(TTree& tree) {
    EMCHit::CreateAllBranch(tree);
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

void EMCSimHit::ConnectToAllBranch(TTree& tree) {
    EMCHit::ConnectToAllBranch(tree);
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
