#include "MACE/DataModel/CDCTrackOperation.hxx"
#include "MACE/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::DataModel::Track {

BranchSocket::Vector3FBranchSocket CDCPhysicsTrack::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::FloatBranchSocket CDCPhysicsTrack::fgVertexEnergy("vtxEne", 0);
BranchSocket::Vector3FBranchSocket CDCPhysicsTrack::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
BranchSocket::ShortStringBranchSocket CDCPhysicsTrack::fgParticle("particle", "");

CDCPhysicsTrack::CDCPhysicsTrack() noexcept :
    CDCTrackBase(),
    fVertexPosition(fgVertexPosition.Value<double>()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value<double>()),
    fParticle(fgParticle.Value()) {}

CDCPhysicsTrack::CDCPhysicsTrack(const CDCHelixTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    CDCTrackBase(static_cast<const CDCTrackBase&>(helix)),
    fVertexPosition(),
    fVertexEnergy(),
    fVertexMomentum(),
    fParticle() {
    const auto [vertexPosition,
                vertexEnergy,
                vertexMomentum,
                particle] =
        CDCTrackOperation::ConvertToPhysicsParameters(std::tuple{VectorCast<Eigen::Vector2d>(helix.GetCenter()),
                                                                 helix.Radius(),
                                                                 helix.GetZ0(),
                                                                 helix.GetAlpha()},
                                                      phiVertex, B, mass);
    VectorAssign(fVertexPosition, vertexPosition);
    fVertexEnergy = vertexEnergy;
    VectorAssign(fVertexMomentum, vertexMomentum);
    fParticle = particle;
}

void CDCPhysicsTrack::FillBranchSockets() const noexcept {
    CDCTrackBase::FillBranchSockets();
    fgVertexPosition.Value(fVertexPosition);
    fgVertexEnergy.Value(fVertexEnergy);
    fgVertexMomentum.Value(fVertexMomentum);
    fgParticle.Value(fParticle);
}

void CDCPhysicsTrack::CreateBranches(TTree& tree) {
    CDCTrackBase::CreateBranches(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
}

void CDCPhysicsTrack::ConnectToBranches(TTree& tree) {
    CDCTrackBase::ConnectToBranches(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
}

} // namespace MACE::DataModel::Track
