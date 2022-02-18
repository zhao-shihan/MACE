#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

Vector2FBranchSocket HelixTrack::fgCenter("Center", 0, 0);
FloatBranchSocket    HelixTrack::fgRadius("R", 0);
FloatBranchSocket        HelixTrack::fgZ0("Z0", 0);
FloatBranchSocket     HelixTrack::fgAlpha("Alpha", 0);
FloatBranchSocket      HelixTrack::fgChi2("Chi2", 0);

HelixTrack::HelixTrack() noexcept :
    Data(),
    fCenter(fgCenter.Value()),
    fRadius(fgRadius.Value()),
    fZ0(fgZ0.Value()),
    fAlpha(fgAlpha.Value()),
    fChi2(fgChi2.Value()) {}

void HelixTrack::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgCenter.BranchName(), fgCenter.Address());
    tree.Branch(fgRadius.BranchName(), fgRadius.Address());
    tree.Branch(fgZ0.BranchName(), fgZ0.Address());
    tree.Branch(fgAlpha.BranchName(), fgAlpha.Address());
    tree.Branch(fgChi2.BranchName(), fgChi2.Address());
}

void HelixTrack::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgCenter.BranchName(), fgCenter.Address());
    tree.SetBranchAddress(fgRadius.BranchName(), fgRadius.Address());
    tree.SetBranchAddress(fgZ0.BranchName(), fgZ0.Address());
    tree.SetBranchAddress(fgAlpha.BranchName(), fgAlpha.Address());
    tree.SetBranchAddress(fgChi2.BranchName(), fgChi2.Address());
}
