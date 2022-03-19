#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket            HelixTrack::fgVertexTime("vtxTime", 0);
Vector2FBranchSocket              HelixTrack::fgCenter("center", { "x", "y" }, { 0, 0 });
FloatBranchSocket                 HelixTrack::fgRadius("r", 0);
FloatBranchSocket                     HelixTrack::fgZ0("z0", 0);
FloatBranchSocket                  HelixTrack::fgAlpha("alpha", 0);
IntBranchSocket     HelixTrack::fgNumberOfFittedPoints("nHits", 0);
FloatBranchSocket                   HelixTrack::fgChi2("chi2", 0);

HelixTrack::HelixTrack() noexcept :
    Base(),
    fVertexTime(fgVertexTime.GetValue()),
    fCenter(fgCenter.GetValue()),
    fRadius(fgRadius.GetValue()),
    fZ0(fgZ0.GetValue()),
    fAlpha(fgAlpha.GetValue()),
    fNumberOfFittedPoints(fgNumberOfFittedPoints.GetValue()),
    fChi2(fgChi2.GetValue()) {}

void HelixTrack::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgVertexTime.CreateBranch(tree);
    fgCenter.CreateBranch(tree);
    fgRadius.CreateBranch(tree);
    fgZ0.CreateBranch(tree);
    fgAlpha.CreateBranch(tree);
    fgNumberOfFittedPoints.CreateBranch(tree);
    fgChi2.CreateBranch(tree);
}

void HelixTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgCenter.ConnectToBranch(tree);
    fgRadius.ConnectToBranch(tree);
    fgZ0.ConnectToBranch(tree);
    fgAlpha.ConnectToBranch(tree);
    fgNumberOfFittedPoints.ConnectToBranch(tree);
    fgChi2.ConnectToBranch(tree);
}
