#ifndef PSIMACEMCPSD_h
#define PSIMACEMCPSD_h 1

#include "G4VSensitiveDetector.hh"
#include "hit/PSIMACEMCPHit.hh"

/// PSIMACEMCP sensitive detector class

class PSIMACEMCPSD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<PSIMACEMCPHit> fMCPHitList;

public:
    PSIMACEMCPSD(const G4String& name);
    virtual ~PSIMACEMCPSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};


#endif
