#include "MACE/Core/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

BranchSocket::FloatBranchSocket CDCSimHit::fgEnergy("hitEne", 0);
BranchSocket::Vector3FBranchSocket CDCSimHit::fgMomentum("hitMom", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::DoubleBranchSocket CDCSimHit::fgVertexTime("vtxTime", 0);
BranchSocket::Vector3FBranchSocket CDCSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::FloatBranchSocket CDCSimHit::fgVertexEnergy("vtxEne", 0);
BranchSocket::Vector3FBranchSocket CDCSimHit::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::ShortStringBranchSocket CDCSimHit::fgParticle("particle", "");
BranchSocket::IntBranchSocket CDCSimHit::fgG4EventID("g4EventID", -1);
BranchSocket::IntBranchSocket CDCSimHit::fgG4TrackID("g4TrackID", -1);

void CDCSimHit::CreateBranches(TTree& tree) {
    CDCHit::CreateBranches(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgMomentum.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
}

void CDCSimHit::ConnectToBranches(TTree& tree) {
    CDCHit::ConnectToBranches(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgMomentum.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::SimHit
