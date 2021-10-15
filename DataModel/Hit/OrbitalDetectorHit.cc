#include "DataModel/Hit/OrbitalDetectorHit.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, HitPositionX, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, HitPositionY, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(OrbitalDetectorHit, HitPositionZ, 0.0);

OrbitalDetectorHit::OrbitalDetectorHit() noexcept :
    Data(),
    fHitTime(0.0),
    fHitPosition() {}

OrbitalDetectorHit::OrbitalDetectorHit(const OrbitalDetectorHit& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fHitPosition(hit.fHitPosition) {}

OrbitalDetectorHit::OrbitalDetectorHit(OrbitalDetectorHit&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fHitPosition(std::move(hit.fHitPosition)) {}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(const OrbitalDetectorHit& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fHitPosition = hit.fHitPosition;
    return *this;
}

OrbitalDetectorHit& OrbitalDetectorHit::operator=(OrbitalDetectorHit&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fHitPosition = std::move(hit.fHitPosition);
    return *this;
}

void OrbitalDetectorHit::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("HitPositionX", &persistHitPositionX);
    tree->Branch("HitPositionY", &persistHitPositionY);
    tree->Branch("HitPositionZ", &persistHitPositionZ);
}

void OrbitalDetectorHit::FillBranches() {
    persistHitTime = fHitTime;
    persistHitPositionX = fHitPosition.x();
    persistHitPositionY = fHitPosition.y();
    persistHitPositionZ = fHitPosition.z();
}