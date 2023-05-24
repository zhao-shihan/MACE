#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCSimTrackBase::Field::PDGCodeTruth::BranchSocket CDCSimTrackBase::Field::PDGCodeTruth::Base::fgBranchSocket =
    {"pdgCodeT", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimTrackBase::Field::NHitTruth::BranchSocket CDCSimTrackBase::Field::NHitTruth::Base::fgBranchSocket =
    {"nHitT", "Number of Hits (MC Truth)", -1};
template<>
CDCSimTrackBase::Field::VertexTimeTruth::BranchSocket CDCSimTrackBase::Field::VertexTimeTruth::Base::fgBranchSocket =
    {"t0T", "Vertex Time (MC Truth)", 0};

inline namespace SimTrack {

void CDCSimTrackBase::CreateAllBranch(TTree& tree) {
    Field::PDGCodeTruth::CreateBranch(tree);
    Field::NHitTruth::CreateBranch(tree);
    Field::VertexTimeTruth::CreateBranch(tree);
}

void CDCSimTrackBase::ConnectToAllBranch(TTree& tree) {
    Field::PDGCodeTruth::ConnectToBranch(tree);
    Field::NHitTruth::ConnectToBranch(tree);
    Field::VertexTimeTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
