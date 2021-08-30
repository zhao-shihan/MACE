#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Hit::CalorimeterHit : public G4VHit {
public:
    CalorimeterHit(
        G4int trackID,
        G4double hitTime,
        const G4ThreeVector& hitPosition);
    ~CalorimeterHit();

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw() override;
    void Print() override;

    const G4int         TrackID;
    const G4double      HitTime;
    const G4ThreeVector HitPosition;
};

namespace MACE {
    namespace SimG4 {
        namespace Hit {

            using CalorimeterHitsCollection = G4THitsCollection<CalorimeterHit>;

            extern G4Allocator<CalorimeterHit>* CalorimeterHitAllocator;

            inline void* CalorimeterHit::operator new(size_t) {
                return static_cast<void*>(CalorimeterHitAllocator->MallocSingle());
            }

            inline void CalorimeterHit::operator delete(void* hit) {
                CalorimeterHitAllocator->FreeSingle(static_cast<CalorimeterHit*>(hit));
            }

        }
    }
}
