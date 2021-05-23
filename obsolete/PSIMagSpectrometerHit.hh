#ifndef PSIMACEMagSpectrometerHit_h
#define PSIMACEMagSpectrometerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4Step.hh"

// PSIMACEMagSpectrometer hit class

class PSIMACEMagSpectrometerHit : public G4VHit {
private:
    G4ThreeVector pos;
    // G4String      particleName;
    G4double      globaltime;
    G4ThreeVector vpos;
    G4int         fChamberNb;

public:
    PSIMACEMagSpectrometerHit();
    PSIMACEMagSpectrometerHit(const PSIMACEMagSpectrometerHit&);
    virtual ~PSIMACEMagSpectrometerHit();

    // operators
    const PSIMACEMagSpectrometerHit& operator=(const PSIMACEMagSpectrometerHit&);
    G4bool operator==(const PSIMACEMagSpectrometerHit& right) const { return this == &right; }

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void        SetPos(G4ThreeVector xyz) { pos = xyz; };
    // void SetParticle(G4String name) { particleName = name; };
    void       SetGlobalTime(G4double t1) { globaltime = t1; };
    void SetVertexPos(G4ThreeVector vxyz) { vpos = vxyz; };
    void        SetChamberNb(G4int chamb) { fChamberNb = chamb; };

    G4ThreeVector       GetPos() const { return pos; };
    // G4String GetParticle()   const { return particleName; };
    G4double     GetGlobalTime() const { return globaltime; };
    G4ThreeVector GetVertexPos() const { return vpos; };
    G4int         GetChamberNb() const { return fChamberNb; };
};

typedef G4THitsCollection<PSIMACEMagSpectrometerHit> PSIMACEMagSpectrometerHitsCollection;

extern G4ThreadLocal G4Allocator<PSIMACEMagSpectrometerHit>* PSIMACEMagSpectrometerHitAllocator;

inline void* PSIMACEMagSpectrometerHit::operator new(size_t) {
    if (!PSIMACEMagSpectrometerHitAllocator)
        PSIMACEMagSpectrometerHitAllocator = new G4Allocator<PSIMACEMagSpectrometerHit>;
    return (void*)PSIMACEMagSpectrometerHitAllocator->MallocSingle();
}

inline void PSIMACEMagSpectrometerHit::operator delete(void* hit) {
    PSIMACEMagSpectrometerHitAllocator->FreeSingle((PSIMACEMagSpectrometerHit*)hit);
}

#endif
