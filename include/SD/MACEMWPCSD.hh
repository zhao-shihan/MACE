#ifndef MACEMWPCSD_h
#define MACEMWPCSD_h 1

#include "G4VSensitiveDetector.hh"
#include "MACEMWPCSD.hh"
#include "hit/MACEMWPCHit.hh"

/// MACEMagSpectrometer sensitive detector class

class MACEMWPCSD : public G4VSensitiveDetector {
private:
    G4ThreadLocal static std::vector<MACEMWPCHit> fMWPCHitList;

public:
    MACEMWPCSD(const G4String& name);
    virtual ~MACEMWPCSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
