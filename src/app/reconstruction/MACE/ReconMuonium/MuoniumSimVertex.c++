#include "MACE/ReconMuonium/MuoniumSimVertex.h++"

namespace MACE::ReconMuonium {

DoubleBranchSocket MuoniumSimVertex::fgTrueVertexTime("trueVtxTime", 0);
Vector3FBranchSocket MuoniumSimVertex::fgTrueVertexPosition("trueVtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket MuoniumSimVertex::fgTrueVertexEnergy("trueVtxEne", 0);
Vector3FBranchSocket MuoniumSimVertex::fgTrueVertexMomentum("trueVtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket MuoniumSimVertex::fgTrueParticles("trueParticles", "");

MuoniumSimVertex::MuoniumSimVertex() noexcept :
    MuoniumVertex(),
    fTrueVertexTime(fgTrueVertexTime.Value()),
    fTrueVertexPosition(fgTrueVertexPosition.Value<double>()),
    fTrueVertexEnergy(fgTrueVertexEnergy.Value()),
    fTrueVertexMomentum(fgTrueVertexMomentum.Value<double>()),
    fTrueParticles(fgTrueParticles.Value()) {}

void MuoniumSimVertex::FillAllBranchSocket() const& noexcept {
    MuoniumVertex::FillAllBranchSocket();
    fgTrueVertexTime.Value(fTrueVertexTime);
    fgTrueVertexPosition.Value(fTrueVertexPosition);
    fgTrueVertexEnergy.Value(fTrueVertexEnergy);
    fgTrueVertexMomentum.Value(fTrueVertexMomentum);
    fgTrueParticles.Value(fTrueParticles);
}

void MuoniumSimVertex::CreateAllBranch(TTree& tree) {
    MuoniumVertex::CreateAllBranch(tree);
    fgTrueVertexTime.CreateBranch(tree);
    fgTrueVertexPosition.CreateBranch(tree);
    fgTrueVertexEnergy.CreateBranch(tree);
    fgTrueVertexMomentum.CreateBranch(tree);
    fgTrueParticles.CreateBranch(tree);
}

void MuoniumSimVertex::ConnectToAllBranch(TTree& tree) {
    MuoniumVertex::ConnectToAllBranch(tree);
    fgTrueVertexTime.ConnectToBranch(tree);
    fgTrueVertexPosition.ConnectToBranch(tree);
    fgTrueVertexEnergy.ConnectToBranch(tree);
    fgTrueVertexMomentum.ConnectToBranch(tree);
    fgTrueParticles.ConnectToBranch(tree);
}

} // namespace MACE::ReconMuonium
