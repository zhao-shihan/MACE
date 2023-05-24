#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCPhysicsSimTrack::Field::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexPositionTruth::Base::fgBranchSocket =  // clang-format off
    {"x0T", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsSimTrack::Field::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexKineticEnergyTruth::Base::fgBranchSocket = 
    {"Ek0T", "Vertex Kinetic Energy (MC Truth)", -114514};
template<>
CDCPhysicsSimTrack::Field::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Field::VertexMomentumTruth::Base::fgBranchSocket =  // clang-format off
    {"p0T", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimTrack {

void CDCPhysicsSimTrack::CreateAllBranch(TTree& tree) {
    CDCPhysicsTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Field::VertexPositionTruth::CreateBranch(tree);
    Field::VertexKineticEnergyTruth::CreateBranch(tree);
    Field::VertexMomentumTruth::CreateBranch(tree);
}

void CDCPhysicsSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCPhysicsTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Field::VertexPositionTruth::ConnectToBranch(tree);
    Field::VertexKineticEnergyTruth::ConnectToBranch(tree);
    Field::VertexMomentumTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
