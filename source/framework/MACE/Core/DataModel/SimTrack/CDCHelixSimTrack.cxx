#include "MACE/Core/DataModel/SimTrack/CDCHelixSimTrack.hxx"
#include "MACE/Core/DataModel/SimTrack/CDCPhysicsSimTrack.hxx"

namespace MACE::Core::DataModel::Track {

BranchSocket::Vector2FBranchSocket CDCHelixSimTrack::fgTrueCenter("trueCenter", {"x", "y"}, {0, 0});
BranchSocket::FloatBranchSocket CDCHelixSimTrack::fgTrueRadius("trueR", 0);
BranchSocket::FloatBranchSocket CDCHelixSimTrack::fgTrueZ0("trueZ0", 0);
BranchSocket::FloatBranchSocket CDCHelixSimTrack::fgTrueAlpha("trueAlpha", 0);

CDCHelixSimTrack::CDCHelixSimTrack() noexcept :
    CDCHelixTrack(),
    CDCSimTrackBase(),
    fTrueCenter(fgTrueCenter.Value<double>()),
    fTrueRadius(fgTrueRadius.Value()),
    fTrueZ0(fgTrueZ0.Value()),
    fTrueAlpha(fgTrueAlpha.Value()) {}

CDCHelixSimTrack::CDCHelixSimTrack(const CDCPhysicsSimTrack& physTrack, Double_t B) :
    CDCHelixTrack(static_cast<const CDCPhysicsTrack&>(physTrack), B),
    CDCSimTrackBase(static_cast<const CDCSimTrackBase&>(physTrack)),
    fTrueCenter(),
    fTrueRadius(),
    fTrueZ0(),
    fTrueAlpha() {
    const auto [trueCenter,
                trueRadius,
                trueZ0,
                trueAlpha] =
        CDCTrackOperation::ConvertToHelixParameters(std::tuple{VectorCast<Eigen::Vector3d>(physTrack.TrueVertexPosition()),
                                                               physTrack.TrueVertexEnergy(),
                                                               VectorCast<Eigen::Vector3d>(physTrack.TrueVertexMomentum()),
                                                               physTrack.GetTrueParticle()},
                                                    B);
    VectorAssign(fTrueCenter, trueCenter);
    fTrueRadius = trueRadius;
    fTrueZ0 = trueZ0;
    fTrueAlpha = trueAlpha;
}

void CDCHelixSimTrack::FillBranchSockets() const noexcept {
    CDCHelixTrack::FillBranchSockets();
    CDCSimTrackBase::FillBranchSockets();
    fgTrueCenter.Value(fTrueCenter);
    fgTrueRadius.Value(fTrueRadius);
    fgTrueZ0.Value(fTrueZ0);
    fgTrueAlpha.Value(fTrueAlpha);
}

void CDCHelixSimTrack::CreateBranches(TTree& tree) {
    CDCHelixTrack::CreateBranches(tree);
    CDCSimTrackBase::CreateBranches(tree);
    fgTrueCenter.CreateBranch(tree);
    fgTrueRadius.CreateBranch(tree);
    fgTrueZ0.CreateBranch(tree);
    fgTrueAlpha.CreateBranch(tree);
}

void CDCHelixSimTrack::ConnectToBranches(TTree& tree) {
    CDCHelixTrack::ConnectToBranches(tree);
    CDCSimTrackBase::ConnectToBranches(tree);
    fgTrueCenter.ConnectToBranch(tree);
    fgTrueRadius.ConnectToBranch(tree);
    fgTrueZ0.ConnectToBranch(tree);
    fgTrueAlpha.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Track
