#include "SimMACE/Hit/VertexDetectorHit.hxx"

using namespace MACE::SimMACE::Hit;

G4Allocator<VertexDetectorHit> MACE::SimMACE::Hit::VertexDetectorHit::fgVertexDetectorAllocator = G4Allocator<VertexDetectorHit>();

VertexDetectorHit::VertexDetectorHit() noexcept :
    G4VHit(),
    DataModel::VertexDetectorSimHit() {}

VertexDetectorHit::VertexDetectorHit(const VertexDetectorHit& hit) noexcept :
    G4VHit(static_cast<const G4VHit&>(hit)),
    DataModel::VertexDetectorSimHit(static_cast<const DataModel::VertexDetectorSimHit&>(hit)) {}

VertexDetectorHit::VertexDetectorHit(VertexDetectorHit&& hit) noexcept :
    G4VHit(static_cast<G4VHit&&>(hit)),
    DataModel::VertexDetectorSimHit(static_cast<DataModel::VertexDetectorSimHit&&>(hit)) {}

VertexDetectorHit& VertexDetectorHit::operator=(const VertexDetectorHit& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<const G4VHit&>(hit));
        DataModel::VertexDetectorSimHit::operator=(static_cast<const DataModel::VertexDetectorSimHit&>(hit));
    }
    return *this;
}

VertexDetectorHit& VertexDetectorHit::operator=(VertexDetectorHit&& hit) noexcept {
    if (std::addressof(hit) != this) {
        G4VHit::operator=(static_cast<G4VHit&&>(hit));
        DataModel::VertexDetectorSimHit::operator=(static_cast<DataModel::VertexDetectorSimHit&&>(hit));
    }
    return *this;
}
