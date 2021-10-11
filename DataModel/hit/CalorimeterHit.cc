#include "DataModel/hit/CalorimeterHit.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(CalorimeterHit, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(CalorimeterHit, Energy, 0.0);

CalorimeterHit::CalorimeterHit() noexcept :
    Data(),
    fHitTime(0.0),
    fEnergy(0.0) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fEnergy(hit.fEnergy) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fEnergy(std::move(hit.fEnergy)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fEnergy = hit.fEnergy;
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fEnergy = std::move(hit.fEnergy);
    return *this;
}

void CalorimeterHit::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("Energy", &persistEnergy);
}

void CalorimeterHit::FillBranches() {
    persistHitTime = fHitTime;
    persistEnergy = fEnergy;
}