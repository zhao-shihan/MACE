#ifndef MACEMCPSD_h
#define MACEMCPSD_h 1

#include "G4VSensitiveDetector.hh"
#include "hit/MACEMCPHit.hh"

/// MACEMCP sensitive detector class

class MACEMCPSD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<MACEMCPHit> fMCPHitList;

public:
    MACEMCPSD(const G4String& name);
    virtual ~MACEMCPSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};


#endif
