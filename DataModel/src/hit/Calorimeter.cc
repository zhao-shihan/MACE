#include "hit/Calorimeter.hh"

using namespace MACE::DataModel::Hit;

MACE_DATA_MODEL_PERSISTIFIER_DEF(Calorimeter, HitTime, 0.0);
MACE_DATA_MODEL_PERSISTIFIER_DEF(Calorimeter, Energy, 0.0);

Calorimeter::Calorimeter() noexcept :
    Data(),
    fHitTime(0.0),
    fEnergy(0.0) {}

Calorimeter::Calorimeter(const Calorimeter& hit) noexcept :
    Data(hit),
    fHitTime(hit.fHitTime),
    fEnergy(hit.fEnergy) {}

Calorimeter::Calorimeter(Calorimeter&& hit) noexcept :
    Data(std::move(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fEnergy(std::move(hit.fEnergy)) {}

Calorimeter& Calorimeter::operator=(const Calorimeter& hit) noexcept {
    Data::operator=(hit);
    fHitTime = hit.fHitTime;
    fEnergy = hit.fEnergy;
    return *this;
}

Calorimeter& Calorimeter::operator=(Calorimeter&& hit) noexcept {
    Data::operator=(std::move(hit));
    fHitTime = std::move(hit.fHitTime);
    fEnergy = std::move(hit.fEnergy);
    return *this;
}

void Calorimeter::CreateBranches(TTree* tree) {
    tree->Branch("HitTime", &persistHitTime);
    tree->Branch("Energy", &persistEnergy);
}

void Calorimeter::FillBranches() {
    persistHitTime = fHitTime;
    persistEnergy = fEnergy;
}