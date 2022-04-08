#include "MACE/Reconstruction/ReconMuonium/MuoniumSimVertex.hxx"

namespace MACE::Reconstruction::ReconMuonium {

DoubleBranchSocket MuoniumSimVertex::fgTrueVertexTime("trueVtxTime", 0);
Vector3FBranchSocket MuoniumSimVertex::fgTrueVertexPosition("trueVtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket MuoniumSimVertex::fgTrueVertexEnergy("trueVtxEne", 0);
Vector3FBranchSocket MuoniumSimVertex::fgTrueVertexMomentum("trueVtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket MuoniumSimVertex::fgTrueParticles("trueParticles", "");

MuoniumSimVertex::MuoniumSimVertex() noexcept :
    MuoniumVertex(),
    fTrueVertexTime(fgTrueVertexTime.GetValue()),
    fTrueVertexPosition(fgTrueVertexPosition.GetValue<Double_t>()),
    fTrueVertexEnergy(fgTrueVertexEnergy.GetValue()),
    fTrueVertexMomentum(fgTrueVertexMomentum.GetValue<Double_t>()),
    fTrueParticles(fgTrueParticles.GetValue()) {}

void MuoniumSimVertex::CreateBranches(TTree& tree) {
    MuoniumVertex::CreateBranches(tree);
    fgTrueVertexTime.CreateBranch(tree);
    fgTrueVertexPosition.CreateBranch(tree);
    fgTrueVertexEnergy.CreateBranch(tree);
    fgTrueVertexMomentum.CreateBranch(tree);
    fgTrueParticles.CreateBranch(tree);
}

void MuoniumSimVertex::ConnectToBranches(TTree& tree) {
    MuoniumVertex::ConnectToBranches(tree);
    fgTrueVertexTime.ConnectToBranch(tree);
    fgTrueVertexPosition.ConnectToBranch(tree);
    fgTrueVertexEnergy.ConnectToBranch(tree);
    fgTrueVertexMomentum.ConnectToBranch(tree);
    fgTrueParticles.ConnectToBranch(tree);
}

void MuoniumSimVertex::FillBranchSockets() const noexcept {
    MuoniumVertex::FillBranchSockets();
    fgTrueVertexTime.SetValue(fTrueVertexTime);
    fgTrueVertexPosition.SetValue(fTrueVertexPosition);
    fgTrueVertexEnergy.SetValue(fTrueVertexEnergy);
    fgTrueVertexMomentum.SetValue(fTrueVertexMomentum);
    fgTrueParticles.SetValue(fTrueParticles);
}

} // namespace MACE::Reconstruction::ReconMuonium
