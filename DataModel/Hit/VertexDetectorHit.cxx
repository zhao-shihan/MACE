#include "DataModel/Hit/VertexDetectorHit.hxx"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Column<Float_t> VertexDetectorHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgHitPositionX = { "HitX", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgHitPositionY = { "HitY", 0.0f };
MACE::DataModel::Column<Float_t> VertexDetectorHit::fgHitPositionZ = { "HitZ", 0.0f };

VertexDetectorHit::VertexDetectorHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fHitPosition(fgHitPositionX.value, fgHitPositionY.value, fgHitPositionZ.value) {}

VertexDetectorHit::VertexDetectorHit(const VertexDetectorHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition) {}

VertexDetectorHit::VertexDetectorHit(VertexDetectorHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}

VertexDetectorHit& VertexDetectorHit::operator=(const VertexDetectorHit& hit) noexcept {
    if (&hit != this) {
        Data::operator=(static_cast<const Data&>(hit));
        fHitTime = hit.fHitTime;
        fHitPosition = hit.fHitPosition;
    }
    return *this;
}

VertexDetectorHit& VertexDetectorHit::operator=(VertexDetectorHit&& hit) noexcept {
    if (&hit != this) {
        Data::operator=(static_cast<Data&&>(hit));
        fHitTime = std::move(hit.fHitTime);
        fHitPosition = std::move(hit.fHitPosition);
    }
    return *this;
}

void VertexDetectorHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->Branch(fgHitPositionX.name, std::addressof(fgHitPositionX.value));
    tree->Branch(fgHitPositionY.name, std::addressof(fgHitPositionY.value));
    tree->Branch(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
}

void VertexDetectorHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, std::addressof(fgHitTime.value));
    tree->SetBranchAddress(fgHitPositionX.name, std::addressof(fgHitPositionX.value));
    tree->SetBranchAddress(fgHitPositionY.name, std::addressof(fgHitPositionY.value));
    tree->SetBranchAddress(fgHitPositionZ.name, std::addressof(fgHitPositionZ.value));
}
