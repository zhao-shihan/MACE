#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"
#include "PhysicalConstant.hxx"

namespace MACE::Core::DataModel::Track {

DoubleBranchSocket PhysicsTrack::fgVertexTime("vtxTime", 0);
Vector3FBranchSocket PhysicsTrack::fgVertexPosition("vtxPos", {"x", "y", "z"}, {0, 0, 0});
FloatBranchSocket PhysicsTrack::fgVertexEnergy("vtxEne", 0);
Vector3FBranchSocket PhysicsTrack::fgVertexMomentum("vtxMom", {"x", "y", "z"}, {0, 0, 0});
ShortStringBranchSocket PhysicsTrack::fgParticle("particle", "");
IntBranchSocket PhysicsTrack::fgNumberOfFittedPoints("nHits", 0);
FloatBranchSocket PhysicsTrack::fgChi2("chi2", 0);

PhysicsTrack::PhysicsTrack() noexcept :
    ITransientData(),
    fVertexTime(fgVertexTime.GetValue()),
    fVertexPosition(fgVertexPosition.GetValue()),
    fVertexEnergy(fgVertexEnergy.GetValue()),
    fVertexMomentum(fgVertexMomentum.GetValue()),
    fParticle(fgParticle.GetValue()),
    fNumberOfFittedPoints(fgNumberOfFittedPoints.GetValue()),
    fChi2(fgChi2.GetValue()) {}

PhysicsTrack::PhysicsTrack(const HelixTrack& helix, Double_t phiVertex, Double_t B, Double_t mass) :
    fVertexTime(helix.GetVertexTime()),
    fNumberOfFittedPoints(helix.GetNumberOfFittedPoints()),
    fChi2(helix.GetChi2()) {
    using Utility::PhysicalConstant::c_light;

    const auto phi0 = helix.CalcPhi0();
    fVertexPosition = helix.CalcPoint(phiVertex, phi0);

    const auto alpha = helix.GetAlpha();
    const auto charge = (alpha > 0) ? (-1) : 1;
    fParticle = (charge > 0) ? "e+" : "e-";

    const auto pPhi = -charge * B * helix.GetRadius() * c_light;
    fVertexMomentum.Set(-pPhi * std::sin(phiVertex + phi0),
                        pPhi * std::cos(phiVertex + phi0),
                        pPhi / std::tan(alpha));
    fVertexEnergy = std::sqrt(fVertexMomentum.Mag2() + mass * mass);
}

void PhysicsTrack::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgParticle.CreateBranch(tree);
    fgNumberOfFittedPoints.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void PhysicsTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgParticle.ConnectToBranch(tree);
    fgNumberOfFittedPoints.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}

void PhysicsTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgVertexEnergy.SetValue(fVertexEnergy);
    fgVertexMomentum.SetValue(fVertexMomentum);
    fgParticle.SetValue(fParticle);
    fgNumberOfFittedPoints.SetValue(fNumberOfFittedPoints);
    fgChi2.SetValue(fChi2);
}

} // namespace MACE::Core::DataModel::Track
