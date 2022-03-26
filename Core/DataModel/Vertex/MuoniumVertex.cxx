#include "DataModel/Vertex/MuoniumVertex.hxx"

namespace MACE::Core::DataModel::Vertex {

DoubleBranchSocket MuoniumVertex::fgTCACDC("TCACDC", 0);
DoubleBranchSocket MuoniumVertex::fgTCAMCP("TCAMCP", 0);
DoubleBranchSocket MuoniumVertex::fgDeltaTCA("DeltaTCA", 0);
Vector3FBranchSocket MuoniumVertex::fgCPACDC("CPACDC", {"x", "y", "z"}, {0, 0, 0});
Vector2FBranchSocket MuoniumVertex::fgCPAMCP("CPAMCP", {"x", "y"}, {0, 0});
FloatBranchSocket MuoniumVertex::fgDCA("DCA", 0);
FloatBranchSocket MuoniumVertex::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket MuoniumVertex::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket MuoniumVertex::fgParticles("particles", "");

MuoniumVertex::MuoniumVertex() noexcept :
    ITransientData(),
    fTCACDC(fgTCACDC.GetValue()),
    fTCAMCP(fgTCAMCP.GetValue()),
    fDeltaTCA(fgDeltaTCA.GetValue()),
    fCPACDC(fgCPACDC.GetValue()),
    fCPAMCP(fgCPAMCP.GetValue()),
    fDCA(fgDCA.GetValue()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue()),
    fParticles(fgParticles.GetValue()) {}

void MuoniumVertex::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgTCACDC.CreateBranch(tree);
    fgTCAMCP.CreateBranch(tree);
    fgDeltaTCA.CreateBranch(tree);
    fgCPACDC.CreateBranch(tree);
    fgCPAMCP.CreateBranch(tree);
    fgDCA.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticles.CreateBranch(tree);
}

void MuoniumVertex::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgTCACDC.ConnectToBranch(tree);
    fgTCAMCP.ConnectToBranch(tree);
    fgDeltaTCA.ConnectToBranch(tree);
    fgCPACDC.ConnectToBranch(tree);
    fgCPAMCP.ConnectToBranch(tree);
    fgDCA.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticles.ConnectToBranch(tree);
}

void MuoniumVertex::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgTCACDC.SetValue(fTCACDC);
    fgTCAMCP.SetValue(fTCAMCP);
    fgDeltaTCA.SetValue(fDeltaTCA);
    fgCPACDC.SetValue(fCPACDC);
    fgCPAMCP.SetValue(fCPAMCP);
    fgDCA.SetValue(fDCA);
    fgVertexEnergy.SetValue(fVertexEnergy);
    fgVertexMomentum.SetValue(fVertexMomentum);
    fgParticles.SetValue(fParticles);
}

} // namespace MACE::Core::DataModel::Vertex
