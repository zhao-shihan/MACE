#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

BranchSocket::IntBranchSocket MCPSimHit::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket MCPSimHit::fgG4TrackID("g4TrackID", -1);
BranchSocket::DoubleBranchSocket MCPSimHit::fgVertexTime("vtxTime", 0);
BranchSocket::Vector3FBranchSocket MCPSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::ShortStringBranchSocket MCPSimHit::fgParticle("particle", "");

void MCPSimHit::CreateBranches(TTree& tree) {
    MCPHit::CreateBranches(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
}

void MCPSimHit::ConnectToBranches(TTree& tree) {
    MCPHit::ConnectToBranches(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimHit
