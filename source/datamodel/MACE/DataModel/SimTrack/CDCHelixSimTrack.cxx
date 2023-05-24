#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.hxx"

namespace MACE::DataModel {

template<>
CDCHelixSimTrack::Field::CenterTruth::BranchSocket CDCHelixSimTrack::Field::CenterTruth::Base::fgBranchSocket = // clang-format off
    {"centerT", "Transverse Center (MC Truth)", {0, 0}}; // clang-format on
template<>
CDCHelixSimTrack::Field::RadiusTruth::BranchSocket CDCHelixSimTrack::Field::RadiusTruth::Base::fgBranchSocket =
    {"rT", "Transverse Radius (MC Truth)", 0};
template<>
CDCHelixSimTrack::Field::VertexZTruth::BranchSocket CDCHelixSimTrack::Field::VertexZTruth::Base::fgBranchSocket =
    {"z0T", "Vertex Z Coordinate (MC Truth)", 0};
template<>
CDCHelixSimTrack::Field::ThetaTruth::BranchSocket CDCHelixSimTrack::Field::ThetaTruth::Base::fgBranchSocket =
    {"thetaT", "Polar Angle (MC Truth)", 0};

inline namespace SimTrack {

void CDCHelixSimTrack::CreateAllBranch(TTree& tree) {
    CDCHelixTrack::CreateAllBranch(tree);
    CDCSimTrackBase::CreateAllBranch(tree);
    Field::CenterTruth::CreateBranch(tree);
    Field::RadiusTruth::CreateBranch(tree);
    Field::VertexZTruth::CreateBranch(tree);
    Field::ThetaTruth::CreateBranch(tree);
}

void CDCHelixSimTrack::ConnectToAllBranch(TTree& tree) {
    CDCHelixTrack::ConnectToAllBranch(tree);
    CDCSimTrackBase::ConnectToAllBranch(tree);
    Field::CenterTruth::ConnectToBranch(tree);
    Field::RadiusTruth::ConnectToBranch(tree);
    Field::VertexZTruth::ConnectToBranch(tree);
    Field::ThetaTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
