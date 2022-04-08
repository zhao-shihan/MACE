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
    fVertexPosition(fgVertexPosition.GetValue<Double_t>()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue<Double_t>()),
    fParticle(fgParticle.GetValue()) {}

CDCPhysicsTrack::CDCPhysicsTrack(const CDCHelixTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    ICDCTrack(static_cast<const ICDCTrack&>(helix)) {
    std::tie(fVertexPosition,
             fVertexEnergy,
             fVertexMomentum,
             fParticle) = CDCTrackOperation::ConvertToPhysicsParameters(std::tie(helix.GetCenter(),
                                                                                 helix.GetRadius(),
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
    fgVertexPosition.SetValue(fVertexPosition);
    fgVertexEnergy.SetValue(fVertexEnergy);
    fgVertexMomentum.SetValue(fVertexMomentum);
    fgParticle.SetValue(fParticle);
}

} // namespace MACE::Core::DataModel::Track
