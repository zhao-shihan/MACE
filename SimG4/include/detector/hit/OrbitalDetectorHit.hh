#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "datamodel/OrbitalDetectorHit.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::OrbitalDetectorHit :
    public MACE::DataModel::OrbitalDetectorHit,
    public G4VHit {
public:
    OrbitalDetectorHit() : DataModel::OrbitalDetectorHit(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
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
