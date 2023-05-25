#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCHelixSimTrack::Column::CenterTruth::BranchSocket CDCHelixSimTrack::Column::CenterTruth::Base::fgBranchSocket = // clang-format off
    {"centerT", "Transverse Center (MC Truth)", {0, 0}}; // clang-format on
template<>
CDCHelixSimTrack::Column::RadiusTruth::BranchSocket CDCHelixSimTrack::Column::RadiusTruth::Base::fgBranchSocket =
    {"rT", "Transverse Radius (MC Truth)", 0};
template<>
CDCHelixSimTrack::Column::VertexZTruth::BranchSocket CDCHelixSimTrack::Column::VertexZTruth::Base::fgBranchSocket =
    {"z0T", "Vertex Z Coordinate (MC Truth)", 0};
template<>
CDCHelixSimTrack::Column::ThetaTruth::BranchSocket CDCHelixSimTrack::Column::ThetaTruth::Base::fgBranchSocket =
    {"thetaT", "Polar Angle (MC Truth)", 0};

inline namespace SimTrack {

void CDCHelixSimTrack::CreateAllBranch(TTree& tree) {
    CDCHelixTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Column::CenterTruth::CreateBranch(tree);
    Column::RadiusTruth::CreateBranch(tree);
    Column::VertexZTruth::CreateBranch(tree);
    Column::ThetaTruth::CreateBranch(tree);
}

void CDCHelixSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCHelixTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Column::CenterTruth::ConnectToBranch(tree);
    Column::RadiusTruth::ConnectToBranch(tree);
    Column::VertexZTruth::ConnectToBranch(tree);
    Column::ThetaTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
