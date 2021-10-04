#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "hit/transient/Calorimeter.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::Calorimeter :
    public MACE::DataModel::Hit::Transient::Calorimeter,
    public G4VHit {
public:
    Calorimeter() : DataModel::Hit::Transient::Calorimeter(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

namespace MACE::SimG4::Hit {

    using CollectionOfCalorimeter = G4THitsCollection<Calorimeter>;

    extern G4Allocator<Calorimeter>* AllocatorOfCalorimeter;

    inline void* Calorimeter::operator new(size_t) {
        return static_cast<void*>(AllocatorOfCalorimeter->MallocSingle());
    }

    inline void Calorimeter::operator delete(void* hit) {
        AllocatorOfCalorimeter->FreeSingle(static_cast<Calorimeter*>(hit));
    }

}
