#include "DataModel/Track/HelixTrack.hxx"

using namespace MACE::DataModel;

Column<Float_t> HelixTrack::fgCenterX = { "Xc", 0.0f };
Column<Float_t> HelixTrack::fgCenterY = { "Yc", 0.0f };
Column<Float_t> HelixTrack::fgRadius = { "R", 0.0f };
Column<Float_t> HelixTrack::fgZ0 = { "Z0", 0.0f };
Column<Float_t> HelixTrack::fgAlpha = { "Alpha", 0.0f };
Column<Float_t> HelixTrack::fgChi2 = { "Chi2", 0.0f };

HelixTrack::HelixTrack() noexcept :
    Data(),
    fCenter(fgCenterX.value, fgCenterY.value),
    fRadius(fgRadius.value),
    fZ0(fgZ0.value),
    fAlpha(fgAlpha.value),
    fChi2(fgChi2.value) {}

void HelixTrack::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgCenterX.name, std::addressof(fgCenterX.value));
    tree.Branch(fgCenterY.name, std::addressof(fgCenterY.value));
    tree.Branch(fgRadius.name, std::addressof(fgRadius.value));
    tree.Branch(fgZ0.name, std::addressof(fgZ0.value));
    tree.Branch(fgAlpha.name, std::addressof(fgAlpha.value));
    tree.Branch(fgChi2.name, std::addressof(fgChi2.value));
}

void HelixTrack::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgCenterX.name, std::addressof(fgCenterX.value));
    tree.SetBranchAddress(fgCenterY.name, std::addressof(fgCenterY.value));
    tree.SetBranchAddress(fgRadius.name, std::addressof(fgRadius.value));
    tree.SetBranchAddress(fgZ0.name, std::addressof(fgZ0.value));
    tree.SetBranchAddress(fgAlpha.name, std::addressof(fgAlpha.value));
    tree.SetBranchAddress(fgChi2.name, std::addressof(fgChi2.value));
}
