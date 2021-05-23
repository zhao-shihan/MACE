#ifndef PSIMACEMWPCSD_h
#define PSIMACEMWPCSD_h 1

#include <list>

#include "G4VSensitiveDetector.hh"
#include "PSIMACEAnalysisManager.hh"

/// PSIMACEMagSpectrometer sensitive detector class

class PSIMACEMWPCSD : public G4VSensitiveDetector {
private:
    static G4ThreadLocal std::vector<std::pair<std::array<G4double, 4>, G4int>> fMagSpecHitList;
    PSIMACEAnalysisManager* fAnalysisManager;

public:
    PSIMACEMWPCSD(const G4String& name);
    virtual ~PSIMACEMWPCSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
