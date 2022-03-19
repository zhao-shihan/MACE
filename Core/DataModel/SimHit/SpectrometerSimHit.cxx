#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket             SpectrometerSimHit::fgEnergy("hitEne", 0);
Vector3FBranchSocket        SpectrometerSimHit::fgMomentum("hitMom", { "x", "y", "z" }, { 0, 0, 0 });
DoubleBranchSocket        SpectrometerSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket  SpectrometerSimHit::fgVertexPosition("vtxPos", { "x", "y", "z" }, { 0, 0, 0 });
FloatBranchSocket       SpectrometerSimHit::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket  SpectrometerSimHit::fgVertexMomentum("vtxMom", { "x", "y", "z" }, { 0, 0, 0 });
ShortStringBranchSocket SpectrometerSimHit::fgParticleName("particle", "");
IntBranchSocket              SpectrometerSimHit::fgEventID("eventID", -1);
IntBranchSocket              SpectrometerSimHit::fgTrackID("trackID", -1);

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    Base(),
    fEnergy(fgEnergy.GetValue()),
    fMomentum(fgMomentum.GetValue()),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue()),
    fParticleName(fgParticleName.GetValue()),
    fEventID(fgEventID.GetValue()),
    fTrackID(fgTrackID.GetValue()) {}

void SpectrometerSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgEnergy.CreateBranch(tree);
    fgMomentum.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticleName.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgEnergy.ConnectToBranch(tree);
    fgMomentum.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticleName.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
