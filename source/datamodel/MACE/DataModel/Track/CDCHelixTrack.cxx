#include "MACE/DataModel/Track/CDCHelixTrack.hxx"

namespace MACE::DataModel {

template<>
CDCHelixTrack::Entry::Center::BranchSocket CDCHelixTrack::Entry::Center::Base::fgBranchSocket =  // clang-format off
    {"center", "Transverse Center", {0, 0}}; // clang-format on
template<>
CDCHelixTrack::Entry::Radius::BranchSocket CDCHelixTrack::Entry::Radius::Base::fgBranchSocket = 
    {"r", "Transverse Radius", 0};
template<>
CDCHelixTrack::Entry::VertexZ::BranchSocket CDCHelixTrack::Entry::VertexZ::Base::fgBranchSocket = 
    {"z0", "Vertex Z Coordinate", 0};
template<>
CDCHelixTrack::Entry::Theta::BranchSocket CDCHelixTrack::Entry::Theta::Base::fgBranchSocket = 
    {"theta", "Polar Angle", 0};

inline namespace Track {

void CDCHelixTrack::CreateAllBranch(TTree& tree) {
    CDCTrackBase::CreateAllBranch(tree);
    Entry::Center::CreateBranch(tree);
    Entry::Radius::CreateBranch(tree);
    Entry::VertexZ::CreateBranch(tree);
    Entry::Theta::CreateBranch(tree);
}

void CDCHelixTrack::ConnectToAllBranch(TTree& tree) {
    CDCTrackBase::ConnectToAllBranch(tree);
    Entry::Center::ConnectToBranch(tree);
    Entry::Radius::ConnectToBranch(tree);
    Entry::VertexZ::ConnectToBranch(tree);
    Entry::Theta::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
