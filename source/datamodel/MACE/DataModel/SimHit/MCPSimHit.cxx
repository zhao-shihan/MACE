#include "MACE/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::DataModel {

template<>
MCPSimHit::Entry::G4EventID::BranchSocket MCPSimHit::Entry::G4EventID::Base::fgBranchSocket = {"g4EventID", -1};
template<>
MCPSimHit::Entry::G4TrackID::BranchSocket MCPSimHit::Entry::G4TrackID::Base::fgBranchSocket = {"g4TrackID", -1};
template<>
MCPSimHit::Entry::PDGCode::BranchSocket MCPSimHit::Entry::PDGCode::Base::fgBranchSocket = {"pdgCode", 0};
template<>
MCPSimHit::Entry::VertexTime::BranchSocket MCPSimHit::Entry::VertexTime::Base::fgBranchSocket = {"vtxTime", 0};
template<> // clang-format off
MCPSimHit::Entry::VertexPosition::BranchSocket MCPSimHit::Entry::VertexPosition::Base::fgBranchSocket = {"vtxPos", {0, 0, 0}}; // clang-format on

inline namespace SimHit {

void MCPSimHit::CreateBranches(TTree& tree) {
    MCPHit::CreateBranches(tree);
    decltype(fG4EventID)::CreateBranch(tree);
    decltype(fG4TrackID)::CreateBranch(tree);
    decltype(fVertexTime)::CreateBranch(tree);
    decltype(fVertexPosition)::CreateBranch(tree);
    decltype(fPDGCode)::CreateBranch(tree);
}

void MCPSimHit::ConnectToBranches(TTree& tree) {
    MCPHit::ConnectToBranches(tree);
    decltype(fG4EventID)::ConnectToBranch(tree);
    decltype(fG4TrackID)::ConnectToBranch(tree);
    decltype(fVertexTime)::ConnectToBranch(tree);
    decltype(fVertexPosition)::ConnectToBranch(tree);
    decltype(fPDGCode)::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
