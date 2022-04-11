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
    fEnergy(fgEnergy.GetValue()),
    fMomentum(fgMomentum.GetValue<double>()),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue<double>()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue<double>()),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

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
    fgEnergy.SetValue(fEnergy);
    fgMomentum.SetValue(fMomentum);
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgVertexEnergy.SetValue(fVertexEnergy);
    fgVertexMomentum.SetValue(fVertexMomentum);
    fgParticle.SetValue(fParticle);
    fgG4EventID.SetValue(fG4EventID);
    fgG4TrackID.SetValue(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
