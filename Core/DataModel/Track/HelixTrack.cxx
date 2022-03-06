#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

FloatBranchSocket   HelixTrack::fgVertexTime("VtxT", 0);
Vector2FBranchSocket    HelixTrack::fgCenter("Center", 0, 0);
FloatBranchSocket       HelixTrack::fgRadius("R", 0);
FloatBranchSocket           HelixTrack::fgZ0("Z0", 0);
FloatBranchSocket        HelixTrack::fgAlpha("Alpha", 0);
FloatBranchSocket         HelixTrack::fgChi2("Chi2", 0);

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
    tree.Branch(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.Branch(fgCenter.BranchName(), fgCenter.Address());
    tree.Branch(fgRadius.BranchName(), fgRadius.Address());
    tree.Branch(fgZ0.BranchName(), fgZ0.Address());
    tree.Branch(fgAlpha.BranchName(), fgAlpha.Address());
    tree.Branch(fgChi2.BranchName(), fgChi2.Address());
}

void HelixTrack::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.SetBranchAddress(fgCenter.BranchName(), fgCenter.Address());
    tree.SetBranchAddress(fgRadius.BranchName(), fgRadius.Address());
    tree.SetBranchAddress(fgZ0.BranchName(), fgZ0.Address());
    tree.SetBranchAddress(fgAlpha.BranchName(), fgAlpha.Address());
    tree.SetBranchAddress(fgChi2.BranchName(), fgChi2.Address());
}
