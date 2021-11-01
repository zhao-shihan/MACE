#include "DataModel/Hit/CalorimeterHit.hh"

using namespace MACE::DataModel::Hit;

MACE::DataModel::Core::Column<Float_t> CalorimeterHit::fgHitTime = { "HitT", 0.0f };
MACE::DataModel::Core::Column<Float_t> CalorimeterHit::fgEnergy = { "Energy", 0.0f };

CalorimeterHit::CalorimeterHit() noexcept :
    Data(),
    fHitTime(fgHitTime.value),
    fEnergy(fgEnergy.value) {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    Data(static_cast<const Data&>(hit)),
    fHitTime(hit.fHitTime),
    fEnergy(hit.fEnergy) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    Data(static_cast<Data&&>(hit)),
    fHitTime(std::move(hit.fHitTime)),
    fEnergy(std::move(hit.fEnergy)) {}

// CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
//     Data::operator=(static_cast<const Data&>(hit));
//     fHitTime = hit.fHitTime;
//     fEnergy = hit.fEnergy;
//     return *this;
// }

// CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
//     Data::operator=(static_cast<Data&&>(hit));
//     fHitTime = std::move(hit.fHitTime);
//     fEnergy = std::move(hit.fEnergy);
//     return *this;
// }

void CalorimeterHit::CreateBranches(TTree* tree) {
    Data::CreateBranches(tree);
    tree->Branch(fgHitTime.name, &fgHitTime.value);
    tree->Branch(fgEnergy.name, &fgEnergy.value);
}

void CalorimeterHit::ReadBranches(TTree* tree) {
    Data::ReadBranches(tree);
    tree->SetBranchAddress(fgHitTime.name, &fgHitTime.value);
    tree->SetBranchAddress(fgEnergy.name, &fgHitTime.value);
}