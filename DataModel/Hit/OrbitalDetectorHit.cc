#include "DataModel/Hit/OrbitalDetectorHit.hh"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgHitPositionX = { "HitX", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgHitPositionY = { "HitY", 0.0f };
MACE::DataModel::Core::Column<Float_t> OrbitalDetectorHit::fgHitPositionZ = { "HitZ", 0.0f };

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fHitPosition(fgHitPositionX.value, fgHitPositionY.value, fgHitPositionZ.value) {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}

// OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
//     Data::operator=(static_cast<const Data&>(hit));
//     fHitTime = hit.fHitTime;
//     fHitPosition = hit.fHitPosition;
//     return *this;
// }

// OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
//     Data::operator=(static_cast<Data&&>(hit));
//     fHitTime = std::move(hit.fHitTime);
//     fHitPosition = std::move(hit.fHitPosition);
//     return *this;
// }

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, &fgHitTime.value);
    tree->Branch(fgHitPositionX.name, &fgHitPositionX.value);
    tree->Branch(fgHitPositionY.name, &fgHitPositionY.value);
    tree->Branch(fgHitPositionZ.name, &fgHitPositionZ.value);
}

void OrbitalDetectorHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, &fgHitTime.value);
    tree->SetBranchAddress(fgHitPositionX.name, &fgHitPositionX.value);
    tree->SetBranchAddress(fgHitPositionY.name, &fgHitPositionY.value);
    tree->SetBranchAddress(fgHitPositionZ.name, &fgHitPositionZ.value);
}
