#include "hit/OrbitalDetector.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, HitPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, HitPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetector, HitPositionZ, 0.0);

OrbitalDetector::OrbitalDetector() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition() {}

OrbitalDetector::OrbitalDetector(const OrbitalDetector& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition) {}

OrbitalDetector::OrbitalDetector(OrbitalDetector&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}

OrbitalDetector& OrbitalDetector::operator=(const OrbitalDetector& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    return *this;
}

OrbitalDetector& OrbitalDetector::operator=(OrbitalDetector&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    return *this;
}

void OrbitalDetector::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("HitPositionX", &persistHitPositionX);
    tree->Branch("HitPositionY", &persistHitPositionY);
    tree->Branch("HitPositionZ", &persistHitPositionZ);
}

void OrbitalDetector::FillBranches() {
    persistHitTime = fHitTime;
    persistHitPositionX = fHitPosition.x();
    persistHitPositionY = fHitPosition.y();
    persistHitPositionZ = fHitPosition.z();
}