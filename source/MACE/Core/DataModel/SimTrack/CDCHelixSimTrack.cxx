#include "MACE/Core/DataModel/SimTrack/CDCHelixSimTrack.hxx"
#include "MACE/Core/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::Core::DataModel::Track {

Vector2FBranchSocket CDCHelixSimTrack::fgTrueCenter("trueCenter", {"x", "y"}, {0, 0});
FloatBranchSocket CDCHelixSimTrack::fgTrueRadius("trueR", 0);
FloatBranchSocket CDCHelixSimTrack::fgTrueZ0("trueZ0", 0);
FloatBranchSocket CDCHelixSimTrack::fgTrueAlpha("trueAlpha", 0);

CDCHelixSimTrack::CDCHelixSimTrack() noexcept :
    CDCHelixTrack(),
    ICDCSimTrack() {
    SetTrueCenter(fgTrueCenter.GetValue<double>());
    SetTrueRadius(fgTrueRadius.GetValue());
    SetTrueZ0(fgTrueZ0.GetValue());
    SetTrueAlpha(fgTrueAlpha.GetValue());
}

CDCHelixSimTrack::CDCHelixSimTrack(const CDCPhysicsSimTrack& physTrack, Double_t B) :
    CDCHelixTrack(static_cast<const CDCPhysicsTrack&>(physTrack), B),
    ICDCSimTrack(static_cast<const ICDCSimTrack&>(physTrack)) {
    std::tie(fTrueCenter,
             fTrueRadius,
             fTrueZ0,
             fTrueAlpha) = CDCTrackOperation::ConvertToHelixParameters(std::tie(physTrack.GetTrueVertexPosition(),
                                                                                physTrack.GetTrueVertexEnergy(),
                                                                                physTrack.GetTrueVertexMomentum(),
                                                                                physTrack.GetTrueParticle()),
                                                                       B);
}

void CDCHelixSimTrack::CreateBranches(TTree& tree) {
    CDCHelixTrack::CreateBranches(tree);
    ICDCSimTrack::CreateBranches(tree);
    fgTrueCenter.CreateBranch(tree);
    fgTrueRadius.CreateBranch(tree);
    fgTrueZ0.CreateBranch(tree);
    fgTrueAlpha.CreateBranch(tree);
}

void CDCHelixSimTrack::ConnectToBranches(TTree& tree) {
    CDCHelixTrack::ConnectToBranches(tree);
    ICDCSimTrack::ConnectToBranches(tree);
    fgTrueCenter.ConnectToBranch(tree);
    fgTrueRadius.ConnectToBranch(tree);
    fgTrueZ0.ConnectToBranch(tree);
    fgTrueAlpha.ConnectToBranch(tree);
}

void CDCHelixSimTrack::FillBranchSockets() const noexcept {
    CDCHelixTrack::FillBranchSockets();
    ICDCSimTrack::FillBranchSockets();
    fgTrueCenter.SetValue(fTrueCenter);
    fgTrueRadius.SetValue(fTrueRadius);
    fgTrueZ0.SetValue(fTrueZ0);
    fgTrueAlpha.SetValue(fTrueAlpha);
}

} // namespace MACE::Core::DataModel::Track
