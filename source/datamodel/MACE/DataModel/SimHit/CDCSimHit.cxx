#include "MACE/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::DataModel {

template<>
CDCSimHit::Entry::G4EventID::BranchSocket CDCSimHit::Entry::G4EventID::Base::fgBranchSocket = {"g4EvtID", -1};
template<>
CDCSimHit::Entry::G4TrackID::BranchSocket CDCSimHit::Entry::G4TrackID::Base::fgBranchSocket = {"g4TrkID", -1};
template<>
CDCSimHit::Entry::PDGCode::BranchSocket CDCSimHit::Entry::PDGCode::Base::fgBranchSocket = {"pdgCode", 0};
template<>
CDCSimHit::Entry::Energy::BranchSocket CDCSimHit::Entry::Energy::Base::fgBranchSocket = {"E", 0};
template<> // clang-format off
CDCSimHit::Entry::Momentum::BranchSocket CDCSimHit::Entry::Momentum::Base::fgBranchSocket = {"p", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Entry::VertexTime::BranchSocket CDCSimHit::Entry::VertexTime::Base::fgBranchSocket = {"t0", 0};
template<> // clang-format off
CDCSimHit::Entry::VertexPosition::BranchSocket CDCSimHit::Entry::VertexPosition::Base::fgBranchSocket = {"x0", {0, 0, 0}}; // clang-format on
template<>
CDCSimHit::Entry::VertexEnergy::BranchSocket CDCSimHit::Entry::VertexEnergy::Base::fgBranchSocket = {"E0", 0};
template<> // clang-format off
CDCSimHit::Entry::VertexMomentum::BranchSocket CDCSimHit::Entry::VertexMomentum::Base::fgBranchSocket = {"p0", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void CDCSimHit::CreateBranches(TTree& tree) {
    CDCHit::CreateBranches(tree);
    decltype(fG4EventID)::CreateBranch(tree);
    decltype(fG4TrackID)::CreateBranch(tree);
    decltype(fPDGCode)::CreateBranch(tree);
    decltype(fEnergy)::CreateBranch(tree);
    decltype(fMomentum)::CreateBranch(tree);
    decltype(fVertexTime)::CreateBranch(tree);
    decltype(fVertexPosition)::CreateBranch(tree);
    decltype(fVertexEnergy)::CreateBranch(tree);
    decltype(fVertexMomentum)::CreateBranch(tree);
}

void CDCSimHit::ConnectToBranches(TTree& tree) {
    CDCHit::ConnectToBranches(tree);
    decltype(fG4EventID)::ConnectToBranch(tree);
    decltype(fG4TrackID)::ConnectToBranch(tree);
    decltype(fPDGCode)::ConnectToBranch(tree);
    decltype(fEnergy)::ConnectToBranch(tree);
    decltype(fMomentum)::ConnectToBranch(tree);
    decltype(fVertexTime)::ConnectToBranch(tree);
    decltype(fVertexPosition)::ConnectToBranch(tree);
    decltype(fVertexEnergy)::ConnectToBranch(tree);
    decltype(fVertexMomentum)::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
