#ifndef PSIMACEGammaCsIHit_h
#define PSIMACEGammaCsIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4Step.hh"

// PMT Scint hit class
// It defines data members to store the trackID, chamberNb, energy deposit,
// and position of charged particles in a selected volume:
// - fTrackID, fChamberNB, fEdep, fPos

class PSIMACEGammaCsIHit : public G4VHit {
private:
    G4double      time;
    // G4String      particleName;
    G4double      energy;

public:
    PSIMACEGammaCsIHit();
    PSIMACEGammaCsIHit(const PSIMACEGammaCsIHit&);
    virtual ~PSIMACEGammaCsIHit();

    // operators
    const PSIMACEGammaCsIHit& operator=(const PSIMACEGammaCsIHit&);
    G4bool operator==(const PSIMACEGammaCsIHit& right) const { return this == &right; }

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // void SetParticle(G4String name) { particleName = name; };
    void   SetTime(G4double t) { time = t; };
    void SetEnergy(G4double E) { energy = E; };

    // G4String GetParticle()        const { return particleName; };
    G4double   GetTime() const { return time; };
    G4double GetEnergy() const { return energy; };
};

typedef G4THitsCollection<PSIMACEGammaCsIHit> PSIMACEGammaCsIHitsCollection;

extern G4ThreadLocal G4Allocator<PSIMACEGammaCsIHit>* PSIMACEGammaCsIHitAllocator;

inline void* PSIMACEGammaCsIHit::operator new(size_t) {
    if (!PSIMACEGammaCsIHitAllocator)
        PSIMACEGammaCsIHitAllocator = new G4Allocator<PSIMACEGammaCsIHit>;
    return (void*)PSIMACEGammaCsIHitAllocator->MallocSingle();
}

inline void PSIMACEGammaCsIHit::operator delete(void* hit) {
    PSIMACEGammaCsIHitAllocator->FreeSingle((PSIMACEGammaCsIHit*)hit);
}

#endif
