#include "Core/DataModel/SimHit/VertexDetectorSimHit.hxx"

namespace MACE::Core::DataModel::SimHit {

DoubleBranchSocket VertexDetectorSimHit::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket VertexDetectorSimHit::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket VertexDetectorSimHit::fgParticle("particle", "");
IntBranchSocket VertexDetectorSimHit::fgEventID("eventID", -1);
IntBranchSocket VertexDetectorSimHit::fgTrackID("trackID", -1);

VertexDetectorSimHit::VertexDetectorSimHit() noexcept :
    VertexDetectorHit(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue()),
    fParticle(fgParticle.GetValue()),
    fEventID(fgEventID.GetValue()),
    fTrackID(fgTrackID.GetValue()) {}

void VertexDetectorSimHit::CreateBranches(TTree& tree) {
    VertexDetectorHit::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void VertexDetectorSimHit::ConnectToBranches(TTree& tree) {
    VertexDetectorHit::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}

void VertexDetectorSimHit::FillBranchSockets() const noexcept {
    VertexDetectorHit::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgParticle.SetValue(fParticle);
    fgEventID.SetValue(fEventID);
    fgTrackID.SetValue(fTrackID);
}

} // namespace MACE::Core::DataModel::SimHit
