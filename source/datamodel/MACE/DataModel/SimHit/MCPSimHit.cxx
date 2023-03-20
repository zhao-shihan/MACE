#include "MACE/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::DataModel::inline SimHit {

IntBranchSocket MCPSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket MCPSimHit::fgG4TrackID("g4TrackID", -1);
DoubleBranchSocket MCPSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket MCPSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket MCPSimHit::fgParticle("particle", "");

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

} // namespace MACE::DataModel::inline SimHit
