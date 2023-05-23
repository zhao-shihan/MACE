#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCHelixSimTrack::Entry::CenterTruth::BranchSocket CDCHelixSimTrack::Entry::CenterTruth::Base::fgBranchSocket = // clang-format off
    {"centerT", "Transverse Center (MC Truth)", {0, 0}}; // clang-format on
template<>
CDCHelixSimTrack::Entry::RadiusTruth::BranchSocket CDCHelixSimTrack::Entry::RadiusTruth::Base::fgBranchSocket =
    {"rT", "Transverse Radius (MC Truth)", 0};
template<>
CDCHelixSimTrack::Entry::VertexZTruth::BranchSocket CDCHelixSimTrack::Entry::VertexZTruth::Base::fgBranchSocket =
    {"z0T", "Vertex Z Coordinate (MC Truth)", 0};
template<>
CDCHelixSimTrack::Entry::ThetaTruth::BranchSocket CDCHelixSimTrack::Entry::ThetaTruth::Base::fgBranchSocket =
    {"thetaT", "Polar Angle (MC Truth)", 0};

inline namespace SimTrack {

void CDCHelixSimTrack::CreateAllBranch(TTree& tree) {
    CDCHelixTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Entry::CenterTruth::CreateBranch(tree);
    Entry::RadiusTruth::CreateBranch(tree);
    Entry::VertexZTruth::CreateBranch(tree);
    Entry::ThetaTruth::CreateBranch(tree);
}

void CDCHelixSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCHelixTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Entry::CenterTruth::ConnectToBranch(tree);
    Entry::RadiusTruth::ConnectToBranch(tree);
    Entry::VertexZTruth::ConnectToBranch(tree);
    Entry::ThetaTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
