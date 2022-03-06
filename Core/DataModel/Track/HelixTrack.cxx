#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

FloatBranchSocket   HelixTrack::fgVertexTime("vtxT", 0);
Vector2FBranchSocket    HelixTrack::fgCenter("center", 0, 0);
FloatBranchSocket       HelixTrack::fgRadius("r", 0);
FloatBranchSocket           HelixTrack::fgZ0("z0", 0);
FloatBranchSocket        HelixTrack::fgAlpha("alpha", 0);
FloatBranchSocket         HelixTrack::fgChi2("chi2", 0);

HelixTrack::HelixTrack() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fCenter(fgCenter.Value()),
    fRadius(fgRadius.Value()),
    fZ0(fgZ0.Value()),
    fAlpha(fgAlpha.Value()),
    fChi2(fgChi2.Value()) {}

void HelixTrack::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgCenter.CreateBranch(tree);
    fgRadius.CreateBranch(tree);
    fgZ0.CreateBranch(tree);
    fgAlpha.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void HelixTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgCenter.ConnectToBranch(tree);
    fgRadius.ConnectToBranch(tree);
    fgZ0.ConnectToBranch(tree);
    fgAlpha.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}
