#include "MACE/ReconMuonium/MuoniumVertex.hxx"

namespace MACE::ReconMuonium {

BranchSocket::DoubleBranchSocket MuoniumVertex::fgTCACDC("TCACDC", 0);
BranchSocket::DoubleBranchSocket MuoniumVertex::fgTCAMCP("TCAMCP", 0);
BranchSocket::DoubleBranchSocket MuoniumVertex::fgDeltaTCA("DeltaTCA", 0);
BranchSocket::Vector3FBranchSocket MuoniumVertex::fgCPACDC("CPACDC", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::Vector2FBranchSocket MuoniumVertex::fgCPAMCP("CPAMCP", {"x", "y"}, {0, 0});
BranchSocket::FloatBranchSocket MuoniumVertex::fgDCA("DCA", 0);
BranchSocket::FloatBranchSocket MuoniumVertex::fgVertexEnergy("vtxEne", 0);
BranchSocket::Vector3FBranchSocket MuoniumVertex::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::ShortStringBranchSocket MuoniumVertex::fgParticles("particles", "");

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

void MuoniumVertex::FillBranchSockets() const noexcept {
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

void MuoniumVertex::CreateBranches(TTree& tree) {
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
