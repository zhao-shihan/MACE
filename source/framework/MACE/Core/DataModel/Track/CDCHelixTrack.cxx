#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

BranchSocket::Vector2FBranchSocket CDCHelixTrack::fgCenter("center", {"x", "y"}, {0, 0});
BranchSocket::FloatBranchSocket CDCHelixTrack::fgRadius("r", 0);
BranchSocket::FloatBranchSocket CDCHelixTrack::fgZ0("z0", 0);
BranchSocket::FloatBranchSocket CDCHelixTrack::fgAlpha("alpha", 0);

CDCHelixTrack::CDCHelixTrack() noexcept :
    CDCTrackBase(),
    fCenter(fgCenter.Value<double>()),
    fRadius(fgRadius.Value()),
    fZ0(fgZ0.Value()),
    fAlpha(fgAlpha.Value()) {}

CDCHelixTrack::CDCHelixTrack(const CDCPhysicsTrack& physTrack, Double_t B) :
    CDCTrackBase(static_cast<const CDCTrackBase&>(physTrack)),
    fCenter(),
    fRadius(),
    fZ0(),
    fAlpha() {
    const auto [center,
                radius,
                z0,
                alpha] =
        CDCTrackOperation::ConvertToHelixParameters(std::tuple{Utility::VectorCast<Eigen::Vector3d>(physTrack.VertexPosition()),
                                                               physTrack.VertexEnergy(),
                                                               Utility::VectorCast<Eigen::Vector3d>(physTrack.VertexMomentum()),
                                                               physTrack.Particle()},
                                                    B);
    Utility::VectorAssign(fCenter, center);
    fRadius = radius;
    fZ0 = z0;
    fAlpha = alpha;
}

void CDCHelixTrack::FillBranchSockets() const noexcept {
    CDCTrackBase::FillBranchSockets();
    fgCenter.Value(fCenter);
    fgRadius.Value(fRadius);
    fgZ0.Value(fZ0);
    fgAlpha.Value(fAlpha);
}

void CDCHelixTrack::CreateBranches(TTree& tree) {
    CDCTrackBase::CreateBranches(tree);
    fgCenter.CreateBranch(tree);
    fgRadius.CreateBranch(tree);
    fgZ0.CreateBranch(tree);
    fgAlpha.CreateBranch(tree);
}

void CDCHelixTrack::ConnectToBranches(TTree& tree) {
    CDCTrackBase::ConnectToBranches(tree);
    fgCenter.ConnectToBranch(tree);
    fgRadius.ConnectToBranch(tree);
    fgZ0.ConnectToBranch(tree);
    fgAlpha.ConnectToBranch(tree);
}

} // namespace MACE::Core::DataModel::Track
