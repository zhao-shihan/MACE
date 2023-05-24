#include "MACE/DataModel/Track/CDCHelixTrack.hxx"

namespace MACE::DataModel {

template<>
CDCHelixTrack::Field::Center::BranchSocket CDCHelixTrack::Field::Center::Base::fgBranchSocket =  // clang-format off
    {"center", "Transverse Center", {0, 0}}; // clang-format on
template<>
CDCHelixTrack::Field::Radius::BranchSocket CDCHelixTrack::Field::Radius::Base::fgBranchSocket = 
    {"r", "Transverse Radius", 0};
template<>
CDCHelixTrack::Field::VertexZ::BranchSocket CDCHelixTrack::Field::VertexZ::Base::fgBranchSocket = 
    {"z0", "Vertex Z Coordinate", 0};
template<>
CDCHelixTrack::Field::Theta::BranchSocket CDCHelixTrack::Field::Theta::Base::fgBranchSocket = 
    {"theta", "Polar Angle", 0};

inline namespace Track {

void CDCHelixTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Field::Center::CreateBranch(tree);
    Field::Radius::CreateBranch(tree);
    Field::VertexZ::CreateBranch(tree);
    Field::Theta::CreateBranch(tree);
}

void CDCHelixTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Field::Center::ConnectToBranch(tree);
    Field::Radius::ConnectToBranch(tree);
    Field::VertexZ::ConnectToBranch(tree);
    Field::Theta::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
