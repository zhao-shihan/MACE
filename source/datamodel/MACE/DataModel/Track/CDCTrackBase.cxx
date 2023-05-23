#include "MACE/DataModel/Track/CDCTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCTrackBase::Entry::PDGCode::BranchSocket CDCTrackBase::Entry::PDGCode::Base::fgBranchSocket = 
    {"pdgCode", "Particle PDG Code", 0};
template<>
CDCTrackBase::Entry::NHit::BranchSocket CDCTrackBase::Entry::NHit::Base::fgBranchSocket = 
    {"nHit", "Number of Hits Fitted", -1};
template<>
CDCTrackBase::Entry::Chi2::BranchSocket CDCTrackBase::Entry::Chi2::Base::fgBranchSocket = 
    {"chi2", "Fitting chi^{2}", -1};
template<>
CDCTrackBase::Entry::VertexTime::BranchSocket CDCTrackBase::Entry::VertexTime::Base::fgBranchSocket = 
    {"t0", "Vertex Time", 0};

inline namespace Track {

void CDCTrackBase::CreateAllBranch(TTree& tree) {
    Entry::PDGCode::CreateBranch(tree);
    Entry::NHit::CreateBranch(tree);
    Entry::Chi2::CreateBranch(tree);
    Entry::VertexTime::CreateBranch(tree);
}

void CDCTrackBase::ConnectToAllBranch(TTree& tree) {
    Entry::PDGCode::ConnectToBranch(tree);
    Entry::NHit::ConnectToBranch(tree);
    Entry::Chi2::ConnectToBranch(tree);
    Entry::VertexTime::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
