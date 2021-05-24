#ifndef PSIMACECsISD_h
#define PSIMACECsISD_h 1

#include "G4VSensitiveDetector.hh"
#include "hit/PSIMACECsIHit.hh"

/// PSIMACEGammaCsI sensitive detector class

class PSIMACECsISD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<PSIMACECsIHit> fCsIHitList;

public:
    PSIMACECsISD(const G4String& name);
    virtual ~PSIMACECsISD();
    
    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
