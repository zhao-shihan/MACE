#include "MACE/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::DataModel {

template<>
EMCalSimHit::Field::MCEventID::BranchSocket EMCalSimHit::Field::MCEventID::Base::fgBranchSocket =
    {"mcEvtID", "MC Event ID", -1};
template<>
EMCalSimHit::Field::MCTrackID::BranchSocket EMCalSimHit::Field::MCTrackID::Base::fgBranchSocket =
    {"mcTrkID", "MC Track ID", -1};
template<>
EMCalSimHit::Field::PDGCode::BranchSocket EMCalSimHit::Field::PDGCode::Base::fgBranchSocket =
    {"pdgCode", "Particle PDG Code (MC Truth)", 0};
template<>
EMCalSimHit::Field::Position::BranchSocket EMCalSimHit::Field::Position::Base::fgBranchSocket = // clang-format off
    {"x", "Hitting Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Field::Momentum::BranchSocket EMCalSimHit::Field::Momentum::Base::fgBranchSocket = // clang-format off
    {"p", "Hitting Momentum (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Field::VertexTime::BranchSocket EMCalSimHit::Field::VertexTime::Base::fgBranchSocket =
    {"t0", "Vertex Time (MC Truth)", 0};
template<>
EMCalSimHit::Field::VertexPosition::BranchSocket EMCalSimHit::Field::VertexPosition::Base::fgBranchSocket = // clang-format off
    {"x0", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Field::VertexKineticEnergy::BranchSocket EMCalSimHit::Field::VertexKineticEnergy::Base::fgBranchSocket =
    {"Ek0", "Vertex Kinetic Energy (MC Truth)", 0};
template<>
EMCalSimHit::Field::VertexMomentum::BranchSocket EMCalSimHit::Field::VertexMomentum::Base::fgBranchSocket = // clang-format off
    {"p0", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void EMCalSimHit::CreateAllBranch(TTree& tree) {
    EMCalHit::CreateAllBranch(tree);
    Field::MCEventID::CreateBranch(tree);
    Field::MCTrackID::CreateBranch(tree);
    Field::PDGCode::CreateBranch(tree);
    Field::Position::CreateBranch(tree);
    Field::Momentum::CreateBranch(tree);
    Field::VertexTime::CreateBranch(tree);
    Field::VertexPosition::CreateBranch(tree);
    Field::VertexKineticEnergy::CreateBranch(tree);
    Field::VertexMomentum::CreateBranch(tree);
}

void EMCalSimHit::ConnectToAllBranch(TTree& tree) {
    EMCalHit::ConnectToAllBranch(tree);
    Field::MCEventID::ConnectToBranch(tree);
    Field::MCTrackID::ConnectToBranch(tree);
    Field::PDGCode::ConnectToBranch(tree);
    Field::Position::ConnectToBranch(tree);
    Field::Momentum::ConnectToBranch(tree);
    Field::VertexTime::ConnectToBranch(tree);
    Field::VertexPosition::ConnectToBranch(tree);
    Field::VertexKineticEnergy::ConnectToBranch(tree);
    Field::VertexMomentum::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
