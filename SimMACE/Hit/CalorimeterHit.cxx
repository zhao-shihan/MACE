#include "SimMACE/Hit/CalorimeterHit.hxx"

using namespace MACE::SimMACE::Hit;

G4Allocator<CalorimeterHit> MACE::SimMACE::Hit::CalorimeterHit::fgCalorimeterHitAllocator = G4Allocator<CalorimeterHit>();

CalorimeterHit::CalorimeterHit() noexcept :
    G4VHit(),
    DataModel::CalorimeterSimHit() {}

CalorimeterHit::CalorimeterHit(const CalorimeterHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::CalorimeterSimHit(static_cast<const DataModel::CalorimeterSimHit&>(hit)) {}

CalorimeterHit::CalorimeterHit(CalorimeterHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::CalorimeterSimHit(static_cast<DataModel::CalorimeterSimHit&&>(hit)) {}

CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<const G4VHit&>(hit));
        DataModel::CalorimeterSimHit::operator=(static_cast<const DataModel::CalorimeterSimHit&>(hit));
    }
    return *this;
}

CalorimeterHit& CalorimeterHit::operator=(CalorimeterHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<G4VHit&&>(hit));
        DataModel::CalorimeterSimHit::operator=(static_cast<DataModel::CalorimeterSimHit&&>(hit));
    }
    return *this;
}
