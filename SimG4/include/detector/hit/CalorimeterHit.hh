#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include "digitized/CalorimeterHit.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::CalorimeterHit :
    public MACE::DataModel::Digitized::CalorimeterHit,
    public G4VHit {
public:
    CalorimeterHit() : DataModel::Digitized::CalorimeterHit(), G4VHit() {}

    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

namespace MACE::SimG4::Hit {

    using CalorimeterHitsCollection = G4THitsCollection<CalorimeterHit>;

    extern G4Allocator<CalorimeterHit>* CalorimeterHitAllocator;

    inline void* CalorimeterHit::operator new(size_t) {
        return static_cast<void*>(CalorimeterHitAllocator->MallocSingle());
    }

    inline void CalorimeterHit::operator delete(void* hit) {
        CalorimeterHitAllocator->FreeSingle(static_cast<CalorimeterHit*>(hit));
    }

}
