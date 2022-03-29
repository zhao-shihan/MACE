#include "Core/DataModel/SimHit/SpectrometerSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

FloatBranchSocket SpectrometerSimHit::fgEnergy("hitEne", 0);
Vector3FBranchSocket SpectrometerSimHit::fgMomentum("hitMom", {"x", "y", "z"}, {0, 0, 0});
DoubleBranchSocket SpectrometerSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket SpectrometerSimHit::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket SpectrometerSimHit::fgParticle("particle", "");
IntBranchSocket SpectrometerSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket SpectrometerSimHit::fgG4TrackID("g4TrackID", -1);

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    SpectrometerHit(),
    fEnergy(fgEnergy.GetValue()),
    fMomentum(fgMomentum.GetValue<Double_t>()),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue<Double_t>()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue<Double_t>()),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

void SpectrometerSimHit::CreateBranches(TTree& tree) {
    SpectrometerHit::CreateBranches(tree);
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

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    SpectrometerHit::ConnectToBranches(tree);
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

void SpectrometerSimHit::FillBranchSockets() const noexcept {
    SpectrometerHit::FillBranchSockets();
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
