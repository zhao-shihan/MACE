#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

DoubleBranchSocket HelixTrack::fgVertexTime("vtxTime", 0);
Vector2FBranchSocket HelixTrack::fgCenter("center", {"x", "y"}, {0, 0});
FloatBranchSocket HelixTrack::fgRadius("r", 0);
FloatBranchSocket HelixTrack::fgZ0("z0", 0);
FloatBranchSocket HelixTrack::fgAlpha("alpha", 0);
IntBranchSocket HelixTrack::fgNumberOfFittedPoints("nHits", 0);
FloatBranchSocket HelixTrack::fgChi2("chi2", 0);

HelixTrack::HelixTrack() noexcept :
    ITransientData(),
    fVertexTime(fgVertexTime.GetValue()),
    fCenter(fgCenter.GetValue()),
    fRadius(fgRadius.GetValue()),
    fZ0(fgZ0.GetValue()),
    fAlpha(fgAlpha.GetValue()),
    fNumberOfFittedPoints(fgNumberOfFittedPoints.GetValue()),
    fChi2(fgChi2.GetValue()) {}

HelixTrack::HelixTrack(const PhysicsTrack& physTrack, Double_t B) :
    fVertexTime(physTrack.GetVertexTime()),
    fNumberOfFittedPoints(physTrack.GetNumberOfFittedPoints()),
    fChi2(physTrack.GetChi2()) {
    using namespace Utility::PhysicalConstant;

    const auto charge = (physTrack.GetParticle().back() == '+') ? 1 : (-1);

    const auto& p = physTrack.GetVertexMomentum();
    const auto pPhi = (charge > 0) ? (-p.Perp()) : p.Perp();
    fRadius = -pPhi / (charge * B * c_light);
    fAlpha = std::atan2(pPhi, p.fZ);

    const auto& [xV, yV, zV] = physTrack.GetVertexPosition();
    fCenter.Set(xV - fRadius * (p.fY / pPhi),
                yV - fRadius * (-p.fX / pPhi));

    fZ0 = zV - fRadius * CalcPhi(xV, yV) / std::tan(fAlpha);
}

TEveVectorD HelixTrack::CalcPoint(Double_t phi, Double_t phi0) const noexcept {
    return TEveVectorD(fCenter.fX + fRadius * std::cos(phi + phi0),
                       fCenter.fY + fRadius * std::sin(phi + phi0),
                       fZ0 + fRadius * phi / std::tan(fAlpha));
}

Double_t HelixTrack::CalcPhi(Double_t x, Double_t y) const noexcept {
    const auto xLocal = x - fCenter.fX;
    const auto yLocal = y - fCenter.fY;
    const auto absPhi = std::acos(-(fCenter.fX * xLocal + fCenter.fY * yLocal) / std::sqrt(fCenter.Mag2() * (xLocal * xLocal + yLocal * yLocal)));
    return (fCenter.fY * xLocal - yLocal * fCenter.fX > 0) ? absPhi : (-absPhi);
}

void HelixTrack::CreateBranches(TTree& tree) {
    ITransientData::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgCenter.CreateBranch(tree);
    fgRadius.CreateBranch(tree);
    fgZ0.CreateBranch(tree);
    fgAlpha.CreateBranch(tree);
    fgNumberOfFittedPoints.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void HelixTrack::ConnectToBranches(TTree& tree) {
    ITransientData::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgCenter.ConnectToBranch(tree);
    fgRadius.ConnectToBranch(tree);
    fgZ0.ConnectToBranch(tree);
    fgAlpha.ConnectToBranch(tree);
    fgNumberOfFittedPoints.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}

void HelixTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgCenter.SetValue(fCenter);
    fgRadius.SetValue(fRadius);
    fgZ0.SetValue(fZ0);
    fgAlpha.SetValue(fAlpha);
    fgNumberOfFittedPoints.SetValue(fNumberOfFittedPoints);
    fgChi2.SetValue(fChi2);
}

} // namespace MACE::Core::DataModel::Track
