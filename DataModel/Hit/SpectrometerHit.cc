#include "DataModel/Hit/SpectrometerHit.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, HitPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, HitPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, HitPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(SpectrometerHit, ChamberID, -1);

SpectrometerHit::SpectrometerHit() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition(),
    fChamberID(-1) {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fChamberID(hit.fChamberID) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fChamberID(std::move(hit.fChamberID)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    fChamberID = hit.fChamberID;
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    fChamberID = std::move(hit.fChamberID);
    return *this;
}

void SpectrometerHit::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("HitPositionX", &persistHitPositionX);
    tree->Branch("HitPositionY", &persistHitPositionY);
    tree->Branch("HitPositionZ", &persistHitPositionZ);
    tree->Branch("ChamberID", &persistChamberID);
}

void SpectrometerHit::FillBranches() {
    persistHitTime = fHitTime;
    persistHitPositionX = fHitPosition.x();
    persistHitPositionY = fHitPosition.y();
    persistHitPositionZ = fHitPosition.z();
    persistChamberID = fChamberID;
}