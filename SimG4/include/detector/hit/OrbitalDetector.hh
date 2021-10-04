#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "hit/transient/OrbitalDetector.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::OrbitalDetector :
    public MACE::DataModel::Hit::Transient::OrbitalDetector,
    public G4VHit {
public:
    OrbitalDetector() : DataModel::Hit::Transient::OrbitalDetector(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

namespace MACE::SimG4::Hit {

    using CollectionOfOrbitalDetector = G4THitsCollection<OrbitalDetector>;

    extern G4Allocator<OrbitalDetector>* AllocatorOfOrbitalDetector;

    inline void* OrbitalDetector::operator new(size_t) {
        return static_cast<void*>(AllocatorOfOrbitalDetector->MallocSingle());
    }

    inline void OrbitalDetector::operator delete(void* hit) {
        AllocatorOfOrbitalDetector->FreeSingle(static_cast<OrbitalDetector*>(hit));
    }

}
