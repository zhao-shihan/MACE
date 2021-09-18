#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::OrbitalDetectorHit : public G4VHit {
public:
    OrbitalDetectorHit(
        G4int trackID,
        G4double vertexTime,
        const G4ThreeVector& vertexPosition,
        G4double hitTime,
        const G4ThreeVector& hitPosition,
        const G4ParticleDefinition* particle);
    // ~OrbitalDetectorHit();

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // void Draw() override;
    // void Print() override;

    const G4int         TrackID;
    const G4double      VertexTime;
    const G4ThreeVector VertexPosition;
    const G4double      HitTime;
    const G4ThreeVector HitPosition;
    const G4ParticleDefinition* const ParticleDefinition;
};

namespace MACE::SimG4::Hit {

    using OrbitalDetectorHitsCollection = G4THitsCollection<OrbitalDetectorHit>;

    extern G4Allocator<OrbitalDetectorHit>* OrbitalDetectorHitAllocator;

    inline void* OrbitalDetectorHit::operator new(size_t) {
        return static_cast<void*>(OrbitalDetectorHitAllocator->MallocSingle());
    }

    inline void OrbitalDetectorHit::operator delete(void* hit) {
        OrbitalDetectorHitAllocator->FreeSingle(static_cast<OrbitalDetectorHit*>(hit));
    }

}
