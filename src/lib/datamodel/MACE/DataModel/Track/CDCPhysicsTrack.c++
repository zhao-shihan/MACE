#include "MACE/DataModel/Track/CDCPhysicsTrack.h++"

namespace MACE::DataModel {

template<>
CDCPhysicsTrack::Column::VertexPosition::BranchSocket CDCPhysicsTrack::Column::VertexPosition::Base::fgBranchSocket =  // clang-format off
    {"x0", "Vertex Position", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsTrack::Column::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Column::VertexKineticEnergy::Base::fgBranchSocket = 
    {"Ek0", "Vertex Kinetic Energy", -114514};
template<>
CDCPhysicsTrack::Column::VertexMomentum::BranchSocket CDCPhysicsTrack::Column::VertexMomentum::Base::fgBranchSocket =  // clang-format off
    {"p0", "Vertex Momentum", {0, 0, 0}}; // clang-format on

inline namespace Track {

void CDCPhysicsTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Column::VertexPosition::CreateBranch(tree);
    Column::VertexKineticEnergy::CreateBranch(tree);
    Column::VertexMomentum::CreateBranch(tree);
}

void CDCPhysicsTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Column::VertexPosition::ConnectToBranch(tree);
    Column::VertexKineticEnergy::ConnectToBranch(tree);
    Column::VertexMomentum::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
