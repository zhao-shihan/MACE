#include "hit/Spectrometer.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, HitPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, HitPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, HitPositionZ, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Spectrometer, ChamberID, -1);

Spectrometer::Spectrometer() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition(),
    fChamberID(-1) {}

Spectrometer::Spectrometer(const Spectrometer& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition),
    fChamberID(hit.fChamberID) {}

Spectrometer::Spectrometer(Spectrometer&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)),
    fChamberID(std::move(hit.fChamberID)) {}

Spectrometer& Spectrometer::operator=(const Spectrometer& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    fChamberID = hit.fChamberID;
    return *this;
}

Spectrometer& Spectrometer::operator=(Spectrometer&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    fChamberID = std::move(hit.fChamberID);
    return *this;
}

void Spectrometer::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("HitPositionX", &persistHitPositionX);
    tree->Branch("HitPositionY", &persistHitPositionY);
    tree->Branch("HitPositionZ", &persistHitPositionZ);
    tree->Branch("ChamberID", &persistChamberID);
}

void Spectrometer::FillBranches() {
    persistHitTime = fHitTime;
    persistHitPositionX = fHitPosition.x();
    persistHitPositionY = fHitPosition.y();
    persistHitPositionZ = fHitPosition.z();
    persistChamberID = fChamberID;
}