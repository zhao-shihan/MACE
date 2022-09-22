#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

BranchSocket::DoubleBranchSocket MCPSimHit::fgVertexTime("vtxTime", 0);
BranchSocket::Vector3FBranchSocket MCPSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::ShortStringBranchSocket MCPSimHit::fgParticle("particle", "");
BranchSocket::IntBranchSocket MCPSimHit::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket MCPSimHit::fgG4TrackID("g4TrackID", -1);

MCPSimHit::MCPSimHit() noexcept :
    MCPHit(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fParticle(fgParticle.Value()),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()) {}

void MCPSimHit::FillBranchSockets() const noexcept {
    MCPHit::FillBranchSockets();
    fgVertexTime.Value(fVertexTime);
    fgVertexPosition.Value(fVertexPosition);
    fgParticle.Value(fParticle);
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
}

void MCPSimHit::CreateBranches(TTree& tree) {
    MCPHit::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void MCPSimHit::ConnectToBranches(TTree& tree) {
    MCPHit::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimHit
