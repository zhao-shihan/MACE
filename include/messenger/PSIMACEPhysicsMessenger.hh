//UICommand for DetetorConstruction and PhysicsList.
#ifndef PSIMACEPhysicsMessenger_h
#define PSIMACEPhysicsMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PSIMACEEmStandardPhysics;
class G4UIdirectory;
class G4UIcmdWithADouble;

class PSIMACEPhysicsMessenger : public G4UImessenger {
public:
    PSIMACEPhysicsMessenger(PSIMACEEmStandardPhysics*);
    virtual ~PSIMACEPhysicsMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    //	PSIMACEDetectorConstruction* fDetectorConstruction;
    PSIMACEEmStandardPhysics* fEmStandardPhysics;

    //	G4UIdirectory*	fDetectorDirectory;
    G4UIdirectory* fPhysicsDirectory;

    G4UIcmdWithADouble* fRDPhysicsCmd; //if there is a rare decay mode for mu+
    G4UIcmdWithADouble* fMMCPhysicsCmd; //if there is a Mu-AntiMu Conversion.
    G4UIcmdWithADouble* fMFPhysicsCmd;  //if there is a MuoniumFormation process.

//	G4UIcmdWithADoubleAndUnit*	fTSLengthCmd;

};

#endif
