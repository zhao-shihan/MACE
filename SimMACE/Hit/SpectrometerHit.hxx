#pragma once

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "SimMACE/Global.hxx"
#include "DataModel/SimHit/SpectrometerSimHit.hxx"

class MACE::SimMACE::Hit::SpectrometerHit :
    public G4VHit,
    public MACE::DataModel::SpectrometerSimHit {
public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept;
    SpectrometerHit(SpectrometerHit&& hit) noexcept;
    ~SpectrometerHit() noexcept {}
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept;

    void SetVertexPosition(const G4ThreeVector& pos) { DataModel::SpectrometerSimHit::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

    inline void* operator new(size_t);
    inline void  operator delete(void*);

private:
    static G4Allocator<SpectrometerHit> fgSpectrometerHitAllocator;
};

namespace MACE::SimMACE::Hit {
    using SpectrometerHitCollection = G4THitsCollection<SpectrometerHit>;
}

inline void* MACE::SimMACE::Hit::SpectrometerHit::
operator new(size_t) {
    return static_cast<void*>(fgSpectrometerHitAllocator.MallocSingle());
}

inline void MACE::SimMACE::Hit::SpectrometerHit::
operator delete(void* hit) {
    fgSpectrometerHitAllocator.FreeSingle(static_cast<SpectrometerHit*>(hit));
}

