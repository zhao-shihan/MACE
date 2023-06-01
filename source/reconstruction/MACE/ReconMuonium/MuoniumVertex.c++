#include "MACE/ReconMuonium/MuoniumVertex.h++"

namespace MACE::ReconMuonium {

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
    fTCACDC(fgTCACDC.Value()),
    fTCAMCP(fgTCAMCP.Value()),
    fDeltaTCA(fgDeltaTCA.Value()),
    fCPACDC(fgCPACDC.Value<double>()),
    fCPAMCP(fgCPAMCP.Value<double>()),
    fDCA(fgDCA.Value()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fParticles(fgParticles.Value()) {}

void MuoniumVertex::FillAllBranchSocket() const& noexcept {
    fgTCACDC.Value(fTCACDC);
    fgTCAMCP.Value(fTCAMCP);
    fgDeltaTCA.Value(fDeltaTCA);
    fgCPACDC.Value(fCPACDC);
    fgCPAMCP.Value(fCPAMCP);
    fgDCA.Value(fDCA);
    fgVertexEnergy.Value(fVertexEnergy);
    fgVertexMomentum.Value(fVertexMomentum);
    fgParticles.Value(fParticles);
}

void MuoniumVertex::CreateAllBranch(TTree& tree) {
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

void MuoniumVertex::ConnectToAllBranch(TTree& tree) {
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

} // namespace MACE::ReconMuonium
