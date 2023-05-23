#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCPhysicsSimTrack::Entry::VertexPositionTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexPositionTruth::Base::fgBranchSocket =  // clang-format off
    {"x0T", "Vertex Position (MC Truth)", {0, 0, 0}}; // clang-format on
template<>
CDCPhysicsSimTrack::Entry::VertexKineticEnergyTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexKineticEnergyTruth::Base::fgBranchSocket = 
    {"Ek0T", "Vertex Kinetic Energy (MC Truth)", -114514};
template<>
CDCPhysicsSimTrack::Entry::VertexMomentumTruth::BranchSocket CDCPhysicsSimTrack::Entry::VertexMomentumTruth::Base::fgBranchSocket =  // clang-format off
    {"p0T", "Vertex Momentum (MC Truth)", {0, 0, 0}}; // clang-format on

inline namespace SimTrack {

void CDCPhysicsSimTrack::CreateAllBranch(TTree& tree) {
    CDCPhysicsTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Entry::VertexPositionTruth::CreateBranch(tree);
    Entry::VertexKineticEnergyTruth::CreateBranch(tree);
    Entry::VertexMomentumTruth::CreateBranch(tree);
}

void CDCPhysicsSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCPhysicsTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Entry::VertexPositionTruth::ConnectToBranch(tree);
    Entry::VertexKineticEnergyTruth::ConnectToBranch(tree);
    Entry::VertexMomentumTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
