#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCSimTrackBase::Entry::PDGCodeTruth::BranchSocket CDCSimTrackBase::Entry::PDGCodeTruth::Base::fgBranchSocket =
    {"pdgCodeT", "Particle PDG Code (MC Truth)", 0};
template<>
CDCSimTrackBase::Entry::NHitTruth::BranchSocket CDCSimTrackBase::Entry::NHitTruth::Base::fgBranchSocket =
    {"nHitT", "Number of Hits (MC Truth)", -1};
template<>
CDCSimTrackBase::Entry::VertexTimeTruth::BranchSocket CDCSimTrackBase::Entry::VertexTimeTruth::Base::fgBranchSocket =
    {"t0T", "Vertex Time (MC Truth)", 0};

inline namespace SimTrack {

void CDCSimTrackBase::CreateAllBranch(TTree& tree) {
    Entry::PDGCodeTruth::CreateBranch(tree);
    Entry::NHitTruth::CreateBranch(tree);
    Entry::VertexTimeTruth::CreateBranch(tree);
}

void CDCSimTrackBase::ConnectToAllBranch(TTree& tree) {
    Entry::PDGCodeTruth::ConnectToBranch(tree);
    Entry::NHitTruth::ConnectToBranch(tree);
    Entry::VertexTimeTruth::ConnectToBranch(tree);
}

} // namespace SimTrack

} // namespace MACE::DataModel
