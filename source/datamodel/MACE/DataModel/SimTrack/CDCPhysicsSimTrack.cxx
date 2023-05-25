#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCPhysicsSimTrack::Column::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexPositionTruth::Base::fgBranchSocket =  // clang-format off
    {"x0T", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsSimTrack::Column::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexKineticEnergyTruth::Base::fgBranchSocket = 
    {"Ek0T", "Vertex Kinetic Energy (MC Truth)", -114514};
template<>
CDCPhysicsSimTrack::Column::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Column::VertexMomentumTruth::Base::fgBranchSocket =  // clang-format off
    {"p0T", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimTrack {

void CDCPhysicsSimTrack::CreateAllBranch(TTree& tree) {
    CDCPhysicsTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Column::VertexPositionTruth::CreateBranch(tree);
    Column::VertexKineticEnergyTruth::CreateBranch(tree);
    Column::VertexMomentumTruth::CreateBranch(tree);
}

void CDCPhysicsSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCPhysicsTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Column::VertexPositionTruth::ConnectToBranch(tree);
    Column::VertexKineticEnergyTruth::ConnectToBranch(tree);
    Column::VertexMomentumTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
