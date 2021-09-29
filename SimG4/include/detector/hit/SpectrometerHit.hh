#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "datamodel/SpectrometerHit.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::SpectrometerHit :
    public MACE::DataModel::SpectrometerHit,
    public G4VHit {
public:
    SpectrometerHit() : DataModel::SpectrometerHit(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
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
