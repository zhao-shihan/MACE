#include "CLHEP/Units/PhysicalConstants.h"

#include "DataModel/Track/PhysicsTrack.hxx"
#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket            PhysicsTrack::fgVertexTime("vtxT", 0);
Vector3FBranchSocket      PhysicsTrack::fgVertexPosition("vtxX", 0, 0, 0);
FloatBranchSocket           PhysicsTrack::fgVertexEnergy("vtxE", 0);
Vector3FBranchSocket      PhysicsTrack::fgVertexMomentum("vtxP", 0, 0, 0);
IntBranchSocket                   PhysicsTrack::fgCharge("q", 0);
IntBranchSocket     PhysicsTrack::fgNumberOfFittedPoints("nPts", 0);
FloatBranchSocket                   PhysicsTrack::fgChi2("chi2", 0);

PhysicsTrack::PhysicsTrack() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value()),
    fCharge(fgCharge.Value()),
    fNumberOfFittedPoints(fgNumberOfFittedPoints.Value()),
    fChi2(fgChi2.Value()) {}

PhysicsTrack::PhysicsTrack(const HelixTrack& helix, UInt_t absQ, Double_t B, Double_t mass) :
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

    fCharge = (alpha > 0) ? (-absQ) : absQ;

    const auto pPhi = -fCharge * B * radius * CLHEP::c_light;
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
    fgCharge.CreateBranch(tree);
    fgNumberOfFittedPoints.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void PhysicsTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgCharge.ConnectToBranch(tree);
    fgNumberOfFittedPoints.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}
