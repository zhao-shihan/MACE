#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

Vector3FBranchSocket CDCPhysicsTrack::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket CDCPhysicsTrack::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket CDCPhysicsTrack::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket CDCPhysicsTrack::fgParticle("particle", "");

CDCPhysicsTrack::CDCPhysicsTrack() noexcept :
    ICDCTrack(),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fParticle(fgParticle.Value()) {}

CDCPhysicsTrack::CDCPhysicsTrack(const CDCHelixTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    ICDCTrack(static_cast<const ICDCTrack&>(helix)),
    fVertexPosition(),
    fVertexEnergy(),
    fVertexMomentum(),
    fParticle() {
    std::tie(fVertexPosition,
             fVertexEnergy,
             fVertexMomentum,
             fParticle) = CDCTrackOperation::ConvertToPhysicsParameters(std::tie(helix.GetCenter(),
                                                                                 helix.Radius(),
                                                                                 helix.GetZ0(),
                                                                                 helix.GetAlpha()),
                                                                        phiVertex, B, mass);
}

void CDCPhysicsTrack::CreateBranches(TTree& tree) {
    ICDCTrack::CreateBranches(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
}

void CDCPhysicsTrack::ConnectToBranches(TTree& tree) {
    ICDCTrack::ConnectToBranches(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
}

void CDCPhysicsTrack::FillBranchSockets() const noexcept {
    ICDCTrack::FillBranchSockets();
    fgVertexPosition.Value(fVertexPosition);
    fgVertexEnergy.Value(fVertexEnergy);
    fgVertexMomentum.Value(fVertexMomentum);
    fgParticle.Value(fParticle);
}

} // namespace MACE::Core::DataModel::Track
