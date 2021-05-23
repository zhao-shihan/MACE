#ifndef PSIMACEMCPSD_h
#define PSIMACEMCPSD_h 1

#include <list>

#include "G4VSensitiveDetector.hh"
#include "PSIMACEAnalysisManager.hh"

/// PSIMACEMCP sensitive detector class

class PSIMACEMCPSD : public G4VSensitiveDetector {
private:
    static G4ThreadLocal std::vector<std::array<G4double, 3>> fMCPHitList;
    PSIMACEAnalysisManager* fAnalysisManager;

public:
    PSIMACEMCPSD(const G4String& name);
    virtual ~PSIMACEMCPSD();

    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};


#endif
