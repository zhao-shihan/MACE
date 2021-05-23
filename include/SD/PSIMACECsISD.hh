#ifndef PSIMACECsISD_h
#define PSIMACECsISD_h 1

#include <list>

#include "G4VSensitiveDetector.hh"
#include "PSIMACEAnalysisManager.hh"

/// PSIMACEGammaCsI sensitive detector class

class PSIMACECsISD : public G4VSensitiveDetector {
private:
    static G4ThreadLocal std::vector<std::array<G4double, 2>> fCsIHitList;
    PSIMACEAnalysisManager* fAnalysisManager;

public:
    PSIMACECsISD(const G4String& name);
    virtual ~PSIMACECsISD();
    
    virtual void   Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);
    virtual void   EndOfEvent(G4HCofThisEvent*);
};

#endif
