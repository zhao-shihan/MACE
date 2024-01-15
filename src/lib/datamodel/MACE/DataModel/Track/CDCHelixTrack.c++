#include "MACE/DataModel/Track/CDCHelixTrack.h++"

namespace MACE::DataModel {

template<>
CDCHelixTrack::Column::Center::BranchSocket CDCHelixTrack::Column::Center::Base::fgBranchSocket =  // clang-format off
    {"center", "Transverse Center", {0, 0}}; // clang-format on
template<>
CDCHelixTrack::Column::Radius::BranchSocket CDCHelixTrack::Column::Radius::Base::fgBranchSocket = 
    {"r", "Transverse Radius", 0};
template<>
CDCHelixTrack::Column::VertexZ::BranchSocket CDCHelixTrack::Column::VertexZ::Base::fgBranchSocket = 
    {"z0", "Vertex Z Coordinate", 0};
template<>
CDCHelixTrack::Column::Theta::BranchSocket CDCHelixTrack::Column::Theta::Base::fgBranchSocket = 
    {"theta", "Polar Angle", 0};

inline namespace Track {

void CDCHelixTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Column::Center::CreateBranch(tree);
    Column::Radius::CreateBranch(tree);
    Column::VertexZ::CreateBranch(tree);
    Column::Theta::CreateBranch(tree);
}

void CDCHelixTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Column::Center::ConnectToBranch(tree);
    Column::Radius::ConnectToBranch(tree);
    Column::VertexZ::ConnectToBranch(tree);
    Column::Theta::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
