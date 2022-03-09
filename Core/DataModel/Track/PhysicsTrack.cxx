#include "CLHEP/Units/PhysicalConstants.h"

#include "DataModel/Track/PhysicsTrack.hxx"
#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket       PhysicsTrack::fgVertexTime("vtxT", 0);
Vector3FBranchSocket PhysicsTrack::fgVertexPosition("vtx", 0, 0, 0);
FloatBranchSocket            PhysicsTrack::fgEnergy("E", 0);
Vector3FBranchSocket       PhysicsTrack::fgMomentum("p", 0, 0, 0);
IntBranchSocket              PhysicsTrack::fgCharge("q", 0);
FloatBranchSocket              PhysicsTrack::fgChi2("chi2", 0);

PhysicsTrack::PhysicsTrack() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fEnergy(fgEnergy.Value()),
    fMomentum(fgMomentum.Value()),
    fCharge(fgCharge.Value()),
    fChi2(fgChi2.Value()) {}

PhysicsTrack::PhysicsTrack(const HelixTrack& helix, UInt_t absQ, Double_t B, Double_t mass) :
    fVertexTime(helix.GetVertexTime()),
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

    fCharge = (alpha > 0) ? (-absQ) : absQ;

    const auto pPhi = -fCharge * B * radius * CLHEP::c_light;
    const auto pX = -pPhi * sinPhi0;
    const auto pY = pPhi * cosPhi0;
    const auto pZ = pPhi / std::tan(alpha);
    fMomentum.Set(pX, pY, pZ);
    fEnergy = std::sqrt(fMomentum.Mag2() + mass * mass);
}

void PhysicsTrack::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgEnergy.CreateBranch(tree);
    fgMomentum.CreateBranch(tree);
    fgCharge.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void PhysicsTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgEnergy.ConnectToBranch(tree);
    fgMomentum.ConnectToBranch(tree);
    fgCharge.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}
