#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::DataModel {

template<>
CDCPhysicsTrack::Entry::VertexPosition::BranchSocket CDCPhysicsTrack::Entry::VertexPosition::Base::fgBranchSocket =  // clang-format off
    {"x0", "Vertex Position", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsTrack::Entry::VertexKineticEnergy::BranchSocket CDCPhysicsTrack::Entry::VertexKineticEnergy::Base::fgBranchSocket = 
    {"Ek0", "Vertex Kinetic Energy", -114514};
template<>
CDCPhysicsTrack::Entry::VertexMomentum::BranchSocket CDCPhysicsTrack::Entry::VertexMomentum::Base::fgBranchSocket =  // clang-format off
    {"p0", "Vertex Momentum", {0, 0, 0}}; // clang-format on

inline namespace Track {

void CDCPhysicsTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Entry::VertexPosition::CreateBranch(tree);
    Entry::VertexKineticEnergy::CreateBranch(tree);
    Entry::VertexMomentum::CreateBranch(tree);
}

void CDCPhysicsTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Entry::VertexPosition::ConnectToBranch(tree);
    Entry::VertexKineticEnergy::ConnectToBranch(tree);
    Entry::VertexMomentum::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
