#include "MACE/Core/DataModel/SimTrack/CDCHelixSimTrack.hxx"
#include "MACE/Core/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::Core::DataModel::Track {

Vector3FBranchSocket CDCPhysicsSimTrack::fgTrueVertexPosition("trueVtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket CDCPhysicsSimTrack::fgTrueVertexEnergy("trueVtxEne", 0);
Vector3FBranchSocket CDCPhysicsSimTrack::fgTrueVertexMomentum("trueVtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket CDCPhysicsSimTrack::fgTrueParticle("trueParticle", "");

CDCPhysicsSimTrack::CDCPhysicsSimTrack() noexcept :
    CDCPhysicsTrack(),
    ICDCSimTrack(),
    fTrueVertexPosition(fgTrueVertexPosition.Value<double>()),
    fTrueVertexEnergy(fgTrueVertexEnergy.Value()),
    fTrueVertexMomentum(fgTrueVertexMomentum.Value<double>()),
    fTrueParticle(fgTrueParticle.Value()) {}

CDCPhysicsSimTrack::CDCPhysicsSimTrack(const CDCHelixSimTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    CDCPhysicsTrack(static_cast<const CDCHelixTrack&>(helix)),
    ICDCSimTrack(static_cast<const ICDCSimTrack&>(helix)),
    fTrueVertexPosition(),
    fTrueVertexEnergy(),
    fTrueVertexMomentum(),
    fTrueParticle() {
    std::tie(fTrueVertexPosition,
             fTrueVertexEnergy,
             fTrueVertexMomentum,
             fTrueParticle) = CDCTrackOperation::ConvertToPhysicsParameters(std::tie(helix.GetTrueCenter(),
                                                                                     helix.GetTrueRadius(),
                                                                                     helix.GetTrueZ0(),
                                                                                     helix.GetTrueAlpha()),
                                                                            phiVertex, B, mass);
}

void CDCPhysicsSimTrack::CreateBranches(TTree& tree) {
    CDCPhysicsTrack::CreateBranches(tree);
    ICDCSimTrack::CreateBranches(tree);
    fgTrueVertexPosition.CreateBranch(tree);
    fgTrueVertexEnergy.CreateBranch(tree);
    fgTrueVertexMomentum.CreateBranch(tree);
    fgTrueParticle.CreateBranch(tree);
}

void CDCPhysicsSimTrack::ConnectToBranches(TTree& tree) {
    CDCPhysicsTrack::ConnectToBranches(tree);
    ICDCSimTrack::ConnectToBranches(tree);
    fgTrueVertexPosition.ConnectToBranch(tree);
    fgTrueVertexEnergy.ConnectToBranch(tree);
    fgTrueVertexMomentum.ConnectToBranch(tree);
    fgTrueParticle.ConnectToBranch(tree);
}

void CDCPhysicsSimTrack::FillBranchSockets() const noexcept {
    CDCPhysicsTrack::FillBranchSockets();
    ICDCSimTrack::FillBranchSockets();
    fgTrueVertexPosition.Value(fTrueVertexPosition);
    fgTrueVertexEnergy.Value(fTrueVertexEnergy);
    fgTrueVertexMomentum.Value(fTrueVertexMomentum);
    fgTrueParticle.Value(fTrueParticle);
}

} // namespace MACE::Core::DataModel::Track
