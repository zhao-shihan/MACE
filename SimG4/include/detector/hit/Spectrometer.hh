#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "hit/transient/Spectrometer.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::Spectrometer :
    public MACE::DataModel::Hit::Transient::Spectrometer,
    public G4VHit {
public:
    Spectrometer() : DataModel::Hit::Transient::Spectrometer(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

namespace MACE::SimG4::Hit {

    using CollectionOfSpectrometer = G4THitsCollection<Spectrometer>;

    extern G4Allocator<Spectrometer>* AllocatorOfSpectrometer;

    inline void* Spectrometer::operator new(size_t) {
        return static_cast<void*>(AllocatorOfSpectrometer->MallocSingle());
    }

    inline void Spectrometer::operator delete(void* hit) {
        AllocatorOfSpectrometer->FreeSingle(static_cast<Spectrometer*>(hit));
    }

}
