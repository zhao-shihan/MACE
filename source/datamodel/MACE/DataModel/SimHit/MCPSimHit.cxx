#include "MACE/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::DataModel {

template<>
MCPSimHit::Entry::G4EventID::BranchSocket MCPSimHit::Entry::G4EventID::Base::fgBranchSocket = {"g4EvtID", -1};
template<>
MCPSimHit::Entry::G4TrackID::BranchSocket MCPSimHit::Entry::G4TrackID::Base::fgBranchSocket = {"g4TrkID", -1};
template<>
MCPSimHit::Entry::PDGCode::BranchSocket MCPSimHit::Entry::PDGCode::Base::fgBranchSocket = {"pdgCode", 0};
template<>
MCPSimHit::Entry::Energy::BranchSocket MCPSimHit::Entry::Energy::Base::fgBranchSocket = {"E", 0};
template<> // clang-format off
MCPSimHit::Entry::Momentum::BranchSocket MCPSimHit::Entry::Momentum::Base::fgBranchSocket = {"p", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket = {"t0", 0};
template<> // clang-format off
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket = {"x0", {0, 0, 0}}; // clang-format on
template<>
MCPSimHit::Entry::VertexEnergy::BranchSocket MCPSimHit::Entry::VertexEnergy::Base::fgBranchSocket = {"E0", 0};
template<> // clang-format off
MCPSimHit::Entry::VertexMomentum::BranchSocket MCPSimHit::Entry::VertexMomentum::Base::fgBranchSocket = {"p0", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void MCPSimHit::CreateBranches(TTree& tree) {
    MCPHit::CreateBranches(tree);
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

void MCPSimHit::ConnectToBranches(TTree& tree) {
    MCPHit::ConnectToBranches(tree);
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
