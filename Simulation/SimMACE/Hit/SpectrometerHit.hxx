#pragma once

#include "G4VHit.hh"
#include "G4TwoVector.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "SimMACE/Global.hxx"
#include "DataModel/SimHit/SpectrometerSimHit.hxx"
#include "ObserverPtr.hxx"

class MACE::SimMACE::SpectrometerHit final :
    public G4VHit,
    public MACE::DataModel::SpectrometerSimHit {
public:
    SpectrometerHit() noexcept = default;
    SpectrometerHit(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit(SpectrometerHit&& hit) noexcept = default;
    ~SpectrometerHit() noexcept = default;
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept = default;

    void SetMomentum(const G4ThreeVector& mom) { DataModel::SpectrometerSimHit::SetMomentum(mom.x(), mom.y(), mom.z()); }
    void SetWirePosition(const G4TwoVector& pos) { DataModel::SpectrometerSimHit::SetWirePosition(pos.x(), pos.y()); }
    void SetVertexPosition(const G4ThreeVector& pos) { DataModel::SpectrometerSimHit::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

    inline void* operator new(size_t);
    inline void  operator delete(void*);

private:
    static ObserverPtr<G4Allocator<SpectrometerHit>> fgSpectrometerHitAllocator;
};

namespace MACE::SimMACE::Hit {
    using SpectrometerHitCollection = G4THitsCollection<SpectrometerHit>;
}

inline void* MACE::SimMACE::SpectrometerHit::
operator new(size_t) {
    if (fgSpectrometerHitAllocator == nullptr) {
        fgSpectrometerHitAllocator = new G4Allocator<SpectrometerHit>();
    }
    return static_cast<void*>(fgSpectrometerHitAllocator->MallocSingle());
}

inline void MACE::SimMACE::SpectrometerHit::
operator delete(void* hit) {
    fgSpectrometerHitAllocator->FreeSingle(static_cast<SpectrometerHit*>(hit));
}
