#include "DataModel/Hit/SpectrometerHit.hh"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitPositionX = { "HitX", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitPositionY = { "HitY", 0.0f };
MACE::DataModel::Column<Float_t> SpectrometerHit::fgHitPositionZ = { "HitZ", 0.0f };
MACE::DataModel::Column<Int_t> SpectrometerHit::fgChamberID = { "CbID", -1 };

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fHitPosition(fgHitPositionX.value, fgHitPositionY.value, fgHitPositionZ.value),
    fChamberID(fgChamberID.value) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fChamberID(hit.fChamberID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fChamberID(std::move(hit.fChamberID)) {}

// SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
//     Data::operator=(static_cast<const Data&>(hit));
//     fHitTime = hit.fHitTime;
//     fHitPosition = hit.fHitPosition;
//     fChamberID = hit.fChamberID;
//     return *this;
// }

// SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
//     Data::operator=(static_cast<Data&&>(hit));
//     fHitTime = std::move(hit.fHitTime);
//     fHitPosition = std::move(hit.fHitPosition);
//     fChamberID = std::move(hit.fChamberID);
//     return *this;
// }

void SpectrometerHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, &fgHitTime.value);
    tree->Branch(fgHitPositionX.name, &fgHitPositionX.value);
    tree->Branch(fgHitPositionY.name, &fgHitPositionY.value);
    tree->Branch(fgHitPositionZ.name, &fgHitPositionZ.value);
    tree->Branch(fgChamberID.name, &fgChamberID.value);
}

void SpectrometerHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, &fgHitTime.value);
    tree->SetBranchAddress(fgHitPositionX.name, &fgHitPositionX.value);
    tree->SetBranchAddress(fgHitPositionY.name, &fgHitPositionY.value);
    tree->SetBranchAddress(fgHitPositionZ.name, &fgHitPositionZ.value);
    tree->SetBranchAddress(fgChamberID.name, &fgChamberID.value);
}
