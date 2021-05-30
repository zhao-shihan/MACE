#ifndef MACECsISD_h
#define MACECsISD_h 1

#include "G4VSensitiveDetector.hh"
#include "hit/MACECsIHit.hh"

/// MACEGammaCsI sensitive detector class

class MACECsISD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<MACECsIHit> fCsIHitList;

public:
    MACECsISD(const G4String& name);
    virtual ~MACECsISD();
    
    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
