#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::DataModel {

template<>
CDCPhysicsTrack::Field::VertexPosition::BranchSocket CDCPhysicsTrack::Field::VertexPosition::Base::fgBranchSocket =  // clang-format off
    {"x0", "Vertex Position", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsTrack::Field::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Field::VertexKineticEnergy::Base::fgBranchSocket = 
    {"Ek0", "Vertex Kinetic Energy", -114514};
template<>
CDCPhysicsTrack::Field::VertexMomentum::BranchSocket CDCPhysicsTrack::Field::VertexMomentum::Base::fgBranchSocket =  // clang-format off
    {"p0", "Vertex Momentum", {0, 0, 0}}; // clang-format on

inline namespace Track {

void CDCPhysicsTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Field::VertexPosition::CreateBranch(tree);
    Field::VertexKineticEnergy::CreateBranch(tree);
    Field::VertexMomentum::CreateBranch(tree);
}

void CDCPhysicsTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Field::VertexPosition::ConnectToBranch(tree);
    Field::VertexKineticEnergy::ConnectToBranch(tree);
    Field::VertexMomentum::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
