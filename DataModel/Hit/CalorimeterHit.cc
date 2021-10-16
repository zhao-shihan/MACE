#include "DataModel/Hit/CalorimeterHit.hh"

using namespace MACE::DataModel::Hit;

Float_t CalorimeterHit::persistHitTime = 0.0f;
Float_t CalorimeterHit::persistEnergy = 0.0f;

CalorimeterHit::CalorimeterHit() noexcept :
    Data(),
    fHitTime(0.0),
    fEnergy(0.0) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fEnergy(hit.fEnergy) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fEnergy(std::move(hit.fEnergy)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    Data::operator=(static_cast<const Data&>(hit));
    fHitTime = hit.fHitTime;
    fEnergy = hit.fEnergy;
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    Data::operator=(static_cast<Data&&>(hit));
    fHitTime = std::move(hit.fHitTime);
    fEnergy = std::move(hit.fEnergy);
    return *this;
}

void CalorimeterHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch("HitT", &persistHitTime);
    tree->Branch("Energy", &persistEnergy);
}