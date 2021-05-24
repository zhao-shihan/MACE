#ifndef PSIMACEMWPCSD_h
#define PSIMACEMWPCSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PSIMACEMWPCSD.hh"
#include "hit/PSIMACEMWPCHit.hh"

/// PSIMACEMagSpectrometer sensitive detector class

class PSIMACEMWPCSD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<PSIMACEMWPCHit> fMWPCHitList;

public:
    PSIMACEMWPCSD(const G4String& name);
    virtual ~PSIMACEMWPCSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
