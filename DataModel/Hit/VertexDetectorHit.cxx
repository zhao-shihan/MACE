#include "DataModel/Hit/VertexDetectorHit.hxx"

using namespace MACE::DataModel;

Column<Float_t> VertexDetectorHit::fgHitTime = { "HitT", 0.0f };
Column<TEveVectorF> VertexDetectorHit::fgHitPosition = { "HitPos", TEveVectorF(0, 0, 0) };

VertexDetectorHit::VertexDetectorHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fHitPosition(fgHitPosition.value) {}

void VertexDetectorHit::CreateBranches(TTree& tree) {
    Data::CreateBranches(tree);
    tree.Branch(fgHitTime.name, std::addressof(fgHitTime.value));
    tree.Branch(fgHitPosition.name, std::addressof(fgHitPosition.value));
}

void VertexDetectorHit::ReadBranches(TTree& tree) {
    Data::ReadBranches(tree);
    tree.SetBranchAddress(fgHitTime.name, std::addressof(fgHitTime.value));
    tree.SetBranchAddress(fgHitPosition.name, std::addressof(fgHitPosition.value));
}
