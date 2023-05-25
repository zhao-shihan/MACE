#include "MACE/DataModel/Track/CDCTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCTrackBase::Column::PDGCode::BranchSocket CDCTrackBase::Column::PDGCode::Base::fgBranchSocket = 
    {"pdgCode", "Particle PDG Code", 0};
template<>
CDCTrackBase::Column::NHit::BranchSocket CDCTrackBase::Column::NHit::Base::fgBranchSocket = 
    {"nHit", "Number of Hits Fitted", -1};
template<>
CDCTrackBase::Column::Chi2::BranchSocket CDCTrackBase::Column::Chi2::Base::fgBranchSocket = 
    {"chi2", "Fitting chi^{2}", -1};
template<>
CDCTrackBase::Column::VertexTime::BranchSocket CDCTrackBase::Column::VertexTime::Base::fgBranchSocket = 
    {"t0", "Vertex Time", 0};

inline namespace Track {

void CDCTrackBase::CreateAllBranch(TTree& tree) {
    Column::PDGCode::CreateBranch(tree);
    Column::NHit::CreateBranch(tree);
    Column::Chi2::CreateBranch(tree);
    Column::VertexTime::CreateBranch(tree);
}

void CDCTrackBase::ConnectToAllBranch(TTree& tree) {
    Column::PDGCode::ConnectToBranch(tree);
    Column::NHit::ConnectToBranch(tree);
    Column::Chi2::ConnectToBranch(tree);
    Column::VertexTime::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
