#include "MACE/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::DataModel {

template<>
EMCalSimHit::Entry::G4EventID::BranchSocket EMCalSimHit::Entry::G4EventID::Base::fgBranchSocket = {"g4EvtID", -1};
template<>
EMCalSimHit::Entry::G4TrackID::BranchSocket EMCalSimHit::Entry::G4TrackID::Base::fgBranchSocket = {"g4TrkID", -1};
template<>
EMCalSimHit::Entry::PDGCode::BranchSocket EMCalSimHit::Entry::PDGCode::Base::fgBranchSocket = {"pdgCode", 0};
template<> // clang-format off
EMCalSimHit::Entry::HitPosition::BranchSocket EMCalSimHit::Entry::HitPosition::Base::fgBranchSocket = {"x", {0, 0, 0}};   // clang-format on
template<> // clang-format off
EMCalSimHit::Entry::Momentum::BranchSocket EMCalSimHit::Entry::Momentum::Base::fgBranchSocket = {"p", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Entry::VertexTime::BranchSocket EMCalSimHit::Entry::VertexTime::Base::fgBranchSocket = {"t0", 0};
template<> // clang-format off
EMCalSimHit::Entry::VertexPosition::BranchSocket EMCalSimHit::Entry::VertexPosition::Base::fgBranchSocket = {"x0", {0, 0, 0}}; // clang-format on
template<>
EMCalSimHit::Entry::VertexEnergy::BranchSocket EMCalSimHit::Entry::VertexEnergy::Base::fgBranchSocket = {"E0", 0};
template<> // clang-format off
EMCalSimHit::Entry::VertexMomentum::BranchSocket EMCalSimHit::Entry::VertexMomentum::Base::fgBranchSocket = {"p0", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void EMCalSimHit::CreateBranches(TTree& tree) {
    EMCalHit::CreateBranches(tree);
    decltype(fG4EventID)::CreateBranch(tree);
    decltype(fG4TrackID)::CreateBranch(tree);
    decltype(fPDGCode)::CreateBranch(tree);
    decltype(fMomentum)::CreateBranch(tree);
    decltype(fVertexTime)::CreateBranch(tree);
    decltype(fVertexPosition)::CreateBranch(tree);
    decltype(fVertexEnergy)::CreateBranch(tree);
    decltype(fVertexMomentum)::CreateBranch(tree);
}

void EMCalSimHit::ConnectToBranches(TTree& tree) {
    EMCalHit::ConnectToBranches(tree);
    decltype(fG4EventID)::ConnectToBranch(tree);
    decltype(fG4TrackID)::ConnectToBranch(tree);
    decltype(fPDGCode)::ConnectToBranch(tree);
    decltype(fMomentum)::ConnectToBranch(tree);
    decltype(fVertexTime)::ConnectToBranch(tree);
    decltype(fVertexPosition)::ConnectToBranch(tree);
    decltype(fVertexEnergy)::ConnectToBranch(tree);
    decltype(fVertexMomentum)::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
