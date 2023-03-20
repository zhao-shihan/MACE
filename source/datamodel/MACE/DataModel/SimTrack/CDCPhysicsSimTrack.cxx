#include "MACE/DataModel/SimTrack/CDCHelixSimTrack.hxx"
#include "MACE/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::DataModel::inline Track {

Vector3FBranchSocket CDCPhysicsSimTrack::fgTrueVertexPosition("trueVtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket CDCPhysicsSimTrack::fgTrueVertexEnergy("trueVtxEne", 0);
Vector3FBranchSocket CDCPhysicsSimTrack::fgTrueVertexMomentum("trueVtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket CDCPhysicsSimTrack::fgTrueParticle("trueParticle", "");

CDCPhysicsSimTrack::CDCPhysicsSimTrack() noexcept :
    CDCPhysicsTrack(),
    CDCSimTrackBase(),
    fTrueVertexPosition(fgTrueVertexPosition.Value<double>()),
    fTrueVertexEnergy(fgTrueVertexEnergy.Value()),
    fTrueVertexMomentum(fgTrueVertexMomentum.Value<double>()),
    fTrueParticle(fgTrueParticle.Value()) {}

CDCPhysicsSimTrack::CDCPhysicsSimTrack(const CDCHelixSimTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    CDCPhysicsTrack(static_cast<const CDCHelixTrack&>(helix)),
    CDCSimTrackBase(static_cast<const CDCSimTrackBase&>(helix)),
    fTrueVertexPosition(),
    fTrueVertexEnergy(),
    fTrueVertexMomentum(),
    fTrueParticle() {
    const auto [trueVertexPosition,
                trueVertexEnergy,
                trueVertexMomentum,
                trueParticle] =
        CDCTrackOperation::ConvertToPhysicsParameters(std::tuple{VectorCast<Eigen::Vector2d>(helix.GetCenter()),
                                                                 helix.Radius(),
                                                                 helix.GetZ0(),
                                                                 helix.GetAlpha()},
                                                      phiVertex, B, mass);
    VectorAssign(fTrueVertexPosition, trueVertexPosition);
    fTrueVertexEnergy = trueVertexEnergy;
    VectorAssign(fTrueVertexMomentum, trueVertexMomentum);
    fTrueParticle = trueParticle;
}

void CDCPhysicsSimTrack::FillBranchSockets() const noexcept {
    CDCPhysicsTrack::FillBranchSockets();
    CDCSimTrackBase::FillBranchSockets();
    fgTrueVertexPosition.Value(fTrueVertexPosition);
    fgTrueVertexEnergy.Value(fTrueVertexEnergy);
    fgTrueVertexMomentum.Value(fTrueVertexMomentum);
    fgTrueParticle.Value(fTrueParticle);
}

void CDCPhysicsSimTrack::CreateBranches(TTree& tree) {
    CDCPhysicsTrack::CreateBranches(tree);
    CDCSimTrackBase::CreateBranches(tree);
    fgTrueVertexPosition.CreateBranch(tree);
    fgTrueVertexEnergy.CreateBranch(tree);
    fgTrueVertexMomentum.CreateBranch(tree);
    fgTrueParticle.CreateBranch(tree);
}

void CDCPhysicsSimTrack::ConnectToBranches(TTree& tree) {
    CDCPhysicsTrack::ConnectToBranches(tree);
    CDCSimTrackBase::ConnectToBranches(tree);
    fgTrueVertexPosition.ConnectToBranch(tree);
    fgTrueVertexEnergy.ConnectToBranch(tree);
    fgTrueVertexMomentum.ConnectToBranch(tree);
    fgTrueParticle.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::inline Track
