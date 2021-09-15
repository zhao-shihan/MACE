#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::SpectrometerHit : public G4VHit {
public:
    SpectrometerHit(
        G4int trackID,
        G4int chamberID,
        G4double vertexTime,
        const G4ThreeVector& vertexPosition,
        G4double hitTime,
        const G4ThreeVector& hitPosition,
        const G4ParticleDefinition* particle);
    // ~SpectrometerHit();

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // void Draw() override;
    // void Print() override;

    const G4int         TrackID;
    const G4int         ChamberID;
    const G4double      VertexTime;
    const G4ThreeVector VertexPosition;
    const G4double      HitTime;
    const G4ThreeVector HitPosition;
    const G4ParticleDefinition* const ParticleDefinition;
};

namespace MACE::SimG4::Hit {

    using SpectrometerHitsCollection = G4THitsCollection<SpectrometerHit>;

    extern G4Allocator<SpectrometerHit>* SpectrometerHitAllocator;

    inline void* SpectrometerHit::operator new(size_t) {
        return static_cast<void*>(SpectrometerHitAllocator->MallocSingle());
    }

    inline void SpectrometerHit::operator delete(void* hit) {
        SpectrometerHitAllocator->FreeSingle(static_cast<SpectrometerHit*>(hit));
    }

}
