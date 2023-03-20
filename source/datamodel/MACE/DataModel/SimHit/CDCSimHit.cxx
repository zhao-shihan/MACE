#include "MACE/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::DataModel::inline SimHit {

FloatBranchSocket CDCSimHit::fgEnergy("hitEne", 0);
Vector3FBranchSocket CDCSimHit::fgMomentum("hitMom", {"x", "y", "z"}, {0, 0, 0});
DoubleBranchSocket CDCSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket CDCSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket CDCSimHit::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket CDCSimHit::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket CDCSimHit::fgParticle("particle", "");
IntBranchSocket CDCSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket CDCSimHit::fgG4TrackID("g4TrackID", -1);

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

} // namespace MACE::DataModel::inline SimHit
