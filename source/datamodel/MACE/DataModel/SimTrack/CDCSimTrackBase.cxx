#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCSimTrackBase::Column::PDGCodeTruth::BranchSocket CDCSimTrackBase::Column::PDGCodeTruth::Base::fgBranchSocket =
    {"pdgCodeT", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimTrackBase::Column::NHitTruth::BranchSocket CDCSimTrackBase::Column::NHitTruth::Base::fgBranchSocket =
    {"nHitT", "Number of Hits (MC Truth)", -1};
template<>
CDCSimTrackBase::Column::VertexTimeTruth::BranchSocket CDCSimTrackBase::Column::VertexTimeTruth::Base::fgBranchSocket =
    {"t0T", "Vertex Time (MC Truth)", 0};

inline namespace SimTrack {

void CDCSimTrackBase::CreateAllBranch(TTree& tree) {
    Column::PDGCodeTruth::CreateBranch(tree);
    Column::NHitTruth::CreateBranch(tree);
    Column::VertexTimeTruth::CreateBranch(tree);
}

void CDCSimTrackBase::ConnectToAllBranch(TTree& tree) {
    Column::PDGCodeTruth::ConnectToBranch(tree);
    Column::NHitTruth::ConnectToBranch(tree);
    Column::VertexTimeTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
