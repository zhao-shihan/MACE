#pragma once

#include "Core/DataModel/SimHit/SpectrometerSimHit.hxx"
#include "Utility/ObserverPtr.hxx"

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::Simulation::SimMACE::Hit {

using Utility::ObserverPtr;

class SpectrometerHit final : public G4VHit,
                              public Core::DataModel::SimHit::SpectrometerSimHit {
    using Base = SpectrometerSimHit;

public:
    SpectrometerHit() noexcept = default;
    SpectrometerHit(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit(SpectrometerHit&& hit) noexcept = default;
    ~SpectrometerHit() noexcept = default;
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept = default;

    void SetWirePosition(const G4TwoVector& pos) { Base::SetWirePosition(pos.x(), pos.y()); }
    void SetWireDirection(const G4ThreeVector& dir) { Base::SetWireDirection(dir.x(), dir.y(), dir.z()); }
    void SetMomentum(const G4ThreeVector& mom) { Base::SetMomentum(mom.x(), mom.y(), mom.z()); }
    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(const G4ThreeVector& mom) { Base::SetVertexMomentum(mom.x(), mom.y(), mom.z()); }

    inline void* operator new(size_t);
    inline void operator delete(void*);

private:
    static ObserverPtr<G4Allocator<SpectrometerHit>> fgSpectrometerHitAllocator;
};

using SpectrometerHitCollection = G4THitsCollection<SpectrometerHit>;

inline void* SpectrometerHit::operator new(size_t) {
    if (fgSpectrometerHitAllocator == nullptr) {
        fgSpectrometerHitAllocator = new G4Allocator<SpectrometerHit>();
    }
    return static_cast<void*>(fgSpectrometerHitAllocator->MallocSingle());
}

inline void SpectrometerHit::operator delete(void* hit) {
    fgSpectrometerHitAllocator->FreeSingle(static_cast<SpectrometerHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
