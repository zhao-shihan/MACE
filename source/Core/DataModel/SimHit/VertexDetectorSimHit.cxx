#include "Core/DataModel/SimHit/VertexDetectorSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

DoubleBranchSocket VertexDetectorSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket VertexDetectorSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket VertexDetectorSimHit::fgParticle("particle", "");
IntBranchSocket VertexDetectorSimHit::fgG4EventID("g4EventID", -1);
IntBranchSocket VertexDetectorSimHit::fgG4TrackID("g4TrackID", -1);

VertexDetectorSimHit::VertexDetectorSimHit() noexcept :
    VertexDetectorHit(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue<Double_t>()),
    fParticle(fgParticle.GetValue()),
    fG4EventID(fgG4EventID.GetValue()),
    fG4TrackID(fgG4TrackID.GetValue()) {}

void VertexDetectorSimHit::CreateBranches(TTree& tree) {
    VertexDetectorHit::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
    fgG4EventID.CreateBranch(tree);
    fgG4TrackID.CreateBranch(tree);
}

void VertexDetectorSimHit::ConnectToBranches(TTree& tree) {
    VertexDetectorHit::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
    fgG4EventID.ConnectToBranch(tree);
    fgG4TrackID.ConnectToBranch(tree);
}

void VertexDetectorSimHit::FillBranchSockets() const noexcept {
    VertexDetectorHit::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgParticle.SetValue(fParticle);
    fgG4EventID.SetValue(fG4EventID);
    fgG4TrackID.SetValue(fG4TrackID);
}

} // namespace MACE::Core::DataModel::SimHit
