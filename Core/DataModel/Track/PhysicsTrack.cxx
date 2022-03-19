#include "CLHEP/Units/PhysicalConstants.h"

#include "DataModel/Track/PhysicsTrack.hxx"
#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket               PhysicsTrack::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket         PhysicsTrack::fgVertexPosition("vtxPos", { "x", "y", "z" }, { 0, 0, 0 });
FloatBranchSocket              PhysicsTrack::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket         PhysicsTrack::fgVertexMomentum("vtxMom", { "x", "y", "z" }, { 0, 0, 0 });
ShortStringBranchSocket        PhysicsTrack::fgParticleName("particle", "");
IntBranchSocket        PhysicsTrack::fgNumberOfFittedPoints("nHits", 0);
FloatBranchSocket                      PhysicsTrack::fgChi2("chi2", 0);

PhysicsTrack::PhysicsTrack() noexcept :
    Base(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue()),
    fParticleName(fgParticleName.GetValue()),
    fNumberOfFittedPoints(fgNumberOfFittedPoints.GetValue()),
    fChi2(fgChi2.GetValue()) {}

PhysicsTrack::PhysicsTrack(const HelixTrack& helix, Double_t B, Double_t mass) :
    fVertexTime(helix.GetVertexTime()),
    fNumberOfFittedPoints(helix.GetNumberOfFittedPoints()),
    fChi2(helix.GetChi2()) {
    const auto& center = helix.GetCenter();
    const auto& radius = helix.GetRadius();
    const auto& vertexZ = helix.GetZ0();
    const auto& alpha = helix.GetAlpha();

    const auto rCenter = center.Mag();
    const auto cosPhi0 = -center.fX / rCenter;
    const auto sinPhi0 = -center.fY / rCenter;
    const auto vertexX = (radius - rCenter) * cosPhi0;
    const auto vertexY = (radius - rCenter) * sinPhi0;
    fVertexPosition.Set(vertexX, vertexY, vertexZ);

    const auto charge = (alpha > 0) ? (-1) : 1;
    fParticleName = (charge > 0) ? "e+" : "e-";

    const auto pPhi = -charge * B * radius * CLHEP::c_light;
    const auto pX = -pPhi * sinPhi0;
    const auto pY = pPhi * cosPhi0;
    const auto pZ = pPhi / std::tan(alpha);
    fVertexMomentum.Set(pX, pY, pZ);
    fVertexEnergy = std::sqrt(fVertexMomentum.Mag2() + mass * mass);
}

void PhysicsTrack::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticleName.CreateBranch(tree);
    fgNumberOfFittedPoints.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void PhysicsTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticleName.ConnectToBranch(tree);
    fgNumberOfFittedPoints.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}
