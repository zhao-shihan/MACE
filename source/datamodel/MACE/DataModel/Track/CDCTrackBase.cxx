#include "MACE/DataModel/Track/CDCTrackBase.hxx"

namespace MACE::DataModel {

template<>
CDCTrackBase::Field::PDGCode::BranchSocket CDCTrackBase::Field::PDGCode::Base::fgBranchSocket = 
    {"pdgCode", "Particle PDG Code", 0};
template<>
CDCTrackBase::Field::NHit::BranchSocket CDCTrackBase::Field::NHit::Base::fgBranchSocket = 
    {"nHit", "Number of Hits Fitted", -1};
template<>
CDCTrackBase::Field::Chi2::BranchSocket CDCTrackBase::Field::Chi2::Base::fgBranchSocket = 
    {"chi2", "Fitting chi^{2}", -1};
template<>
CDCTrackBase::Field::VertexTime::BranchSocket CDCTrackBase::Field::VertexTime::Base::fgBranchSocket = 
    {"t0", "Vertex Time", 0};

inline namespace Track {

void CDCTrackBase::CreateAllBranch(TTree& tree) {
    Field::PDGCode::CreateBranch(tree);
    Field::NHit::CreateBranch(tree);
    Field::Chi2::CreateBranch(tree);
    Field::VertexTime::CreateBranch(tree);
}

void CDCTrackBase::ConnectToAllBranch(TTree& tree) {
    Field::PDGCode::ConnectToBranch(tree);
    Field::NHit::ConnectToBranch(tree);
    Field::Chi2::ConnectToBranch(tree);
    Field::VertexTime::ConnectToBranch(tree);
}

} // namespace Track

} // namespace MACE::DataModel
