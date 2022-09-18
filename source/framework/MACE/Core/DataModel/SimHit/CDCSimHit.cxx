#include "MACE/Core/DataModel/SimHit/CDCSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

FloatBranchSocket CDCSimHit::fgEnergy("hitEne", 0);
Vector3FBranchSocket CDCSimHit::fgMomentum("hitMom", {"x", "y", "z"}, {0, 0, 0});
DoubleBranchSocket CDCSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket CDCSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket CDCSimHit::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket CDCSimHit::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket CDCSimHit::fgParticle("particle", "");
IntBranchSocket CDCSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket CDCSimHit::fgG4TrackID("g4TrackID", -1);

CDCSimHit::CDCSimHit() noexcept :
    CDCHit(),
    fEnergy(fgEnergy.Value()),
    fMomentum(fgMomentum.Value<double>()),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fParticle(fgParticle.Value()),
    fG4EventID(fgG4EventID.Value()),
    fG4TrackID(fgG4TrackID.Value()) {}

void CDCSimHit::CreateBranches(TTree& tree) {
    CDCHit::CreateBranches(tree);
    fgEnergy.CreateBranch(tree);
    fgMomentum.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void CDCSimHit::ConnectToBranches(TTree& tree) {
    CDCHit::ConnectToBranches(tree);
    fgEnergy.ConnectToBranch(tree);
    fgMomentum.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

void CDCSimHit::FillBranchSockets() const noexcept {
    CDCHit::FillBranchSockets();
    fgEnergy.Value(fEnergy);
    fgMomentum.Value(fMomentum);
    fgVertexTime.Value(fVertexTime);
    fgVertexPosition.Value(fVertexPosition);
    fgVertexEnergy.Value(fVertexEnergy);
    fgVertexMomentum.Value(fVertexMomentum);
    fgParticle.Value(fParticle);
    fgG4EventID.Value(fG4EventID);
    fgG4TrackID.Value(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
