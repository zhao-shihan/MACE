#ifndef PSIMACEMCPHit_h
#define PSIMACEMCPHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4Step.hh"

// MicroChannel Plate hit class
class PSIMACEMCPHit : public G4VHit {
private:
    G4ThreeVector pos;
    G4ThreeVector vpos;
    G4double      globaltime;
    // G4String      particleName;

public:
    PSIMACEMCPHit();
    PSIMACEMCPHit(const PSIMACEMCPHit&);
    virtual ~PSIMACEMCPHit();

    // operators
    const PSIMACEMCPHit& operator=(const PSIMACEMCPHit&);
    G4bool operator==(const PSIMACEMCPHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void        SetPos(G4ThreeVector xyz) { pos = xyz; };
    void SetVertexPos(G4ThreeVector vxyz) { vpos = vxyz; };
    // void SetParticle(G4String name) { particleName = name; };
    void       SetGlobalTime(G4double t2) { globaltime = t2; };

    G4ThreeVector       GetPos() const { return pos; };
    G4ThreeVector GetVertexPos() const { return vpos; };
    // G4String GetParticle() { return particleName; };
    G4double     GetGlobalTime() const { return globaltime; };
};

typedef G4THitsCollection<PSIMACEMCPHit> PSIMACEMCPHitsCollection;

extern G4ThreadLocal G4Allocator<PSIMACEMCPHit>* PSIMACEMCPHitAllocator;

inline void* PSIMACEMCPHit::operator new(size_t) {
    if (!PSIMACEMCPHitAllocator)
        PSIMACEMCPHitAllocator = new G4Allocator<PSIMACEMCPHit>;
    return (void*)PSIMACEMCPHitAllocator->MallocSingle();
}

inline void PSIMACEMCPHit::operator delete(void* hit) {
    PSIMACEMCPHitAllocator->FreeSingle((PSIMACEMCPHit*)hit);
}


#endif
