#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

Vector2FBranchSocket CDCHelixTrack::fgCenter("center", {"x", "y"}, {0, 0});
FloatBranchSocket CDCHelixTrack::fgRadius("r", 0);
FloatBranchSocket CDCHelixTrack::fgZ0("z0", 0);
FloatBranchSocket CDCHelixTrack::fgAlpha("alpha", 0);

CDCHelixTrack::CDCHelixTrack() noexcept :
    ICDCTrack(),
    fCenter(fgCenter.GetValue<double>()),
    fRadius(fgRadius.GetValue()),
    fZ0(fgZ0.GetValue()),
    fAlpha(fgAlpha.GetValue()) {}

CDCHelixTrack::CDCHelixTrack(const CDCPhysicsTrack& physTrack, Double_t B) :
    ICDCTrack(static_cast<const ICDCTrack&>(physTrack)),
    fCenter(),
    fRadius(),
    fZ0(),
    fAlpha() {
    std::tie(fCenter,
             fRadius,
             fZ0,
             fAlpha) = CDCTrackOperation::ConvertToHelixParameters(std::tie(physTrack.GetVertexPosition(),
                                                                            physTrack.GetVertexEnergy(),
                                                                            physTrack.GetVertexMomentum(),
                                                                            physTrack.GetParticle()),
                                                                   B);
}

void CDCHelixTrack::CreateBranches(TTree& tree) {
    ICDCTrack::CreateBranches(tree);
    fgCenter.CreateBranch(tree);
    fgRadius.CreateBranch(tree);
    fgZ0.CreateBranch(tree);
    fgAlpha.CreateBranch(tree);
}

void CDCHelixTrack::ConnectToBranches(TTree& tree) {
    ICDCTrack::ConnectToBranches(tree);
    fgCenter.ConnectToBranch(tree);
    fgRadius.ConnectToBranch(tree);
    fgZ0.ConnectToBranch(tree);
    fgAlpha.ConnectToBranch(tree);
}

void CDCHelixTrack::FillBranchSockets() const noexcept {
    ICDCTrack::FillBranchSockets();
    fgCenter.SetValue(fCenter);
    fgRadius.SetValue(fRadius);
    fgZ0.SetValue(fZ0);
    fgAlpha.SetValue(fAlpha);
}

} // namespace MACE::Core::DataModel::Track
