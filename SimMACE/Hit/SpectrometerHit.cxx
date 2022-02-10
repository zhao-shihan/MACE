#include "SimMACE/Hit/SpectrometerHit.hxx"

using namespace MACE::SimMACE::Hit;

G4Allocator<SpectrometerHit> MACE::SimMACE::Hit::SpectrometerHit::fgSpectrometerHitAllocator = G4Allocator<SpectrometerHit>();

SpectrometerHit::SpectrometerHit() noexcept :
    G4VHit(),
    DataModel::SpectrometerSimHit() {}

SpectrometerHit::SpectrometerHit(const SpectrometerHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::SpectrometerSimHit(static_cast<const DataModel::SpectrometerSimHit&>(hit)) {}

SpectrometerHit::SpectrometerHit(SpectrometerHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::SpectrometerSimHit(static_cast<DataModel::SpectrometerSimHit&&>(hit)) {}

SpectrometerHit& SpectrometerHit::operator=(const SpectrometerHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<const G4VHit&>(hit));
        DataModel::SpectrometerSimHit::operator=(static_cast<const DataModel::SpectrometerSimHit&>(hit));
    }
    return *this;
}

SpectrometerHit& SpectrometerHit::operator=(SpectrometerHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<G4VHit&&>(hit));
        DataModel::SpectrometerSimHit::operator=(static_cast<DataModel::SpectrometerSimHit&&>(hit));
    }
    return *this;
}
