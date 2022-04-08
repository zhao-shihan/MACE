#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

DoubleBranchSocket MCPSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket MCPSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket MCPSimHit::fgParticle("particle", "");
IntBranchSocket MCPSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket MCPSimHit::fgG4TrackID("g4TrackID", -1);

MCPSimHit::MCPSimHit() noexcept :
    MCPHit(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue<Double_t>()),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

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

void MCPSimHit::FillBranchSockets() const noexcept {
    MCPHit::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgParticle.SetValue(fParticle);
    fgG4EventID.SetValue(fG4EventID);
    fgG4TrackID.SetValue(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
