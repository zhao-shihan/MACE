//UICommand for DetetorConstruction and PhysicsList.
#ifndef MACEPhysicsMessenger_h
#define MACEPhysicsMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MACEEmStandardPhysics;
class G4UIdirectory;
class G4UIcmdWithADouble;

class MACEPhysicsMessenger : public G4UImessenger {
public:
    MACEPhysicsMessenger(MACEEmStandardPhysics*);
    virtual ~MACEPhysicsMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    //	MACEDetectorConstruction* fDetectorConstruction;
    MACEEmStandardPhysics* fEmStandardPhysics;

    //	G4UIdirectory*	fDetectorDirectory;
    G4UIdirectory* fPhysicsDirectory;

    G4UIcmdWithADouble* fRDPhysicsCmd; //if there is a rare decay mode for mu+
    G4UIcmdWithADouble* fMMCPhysicsCmd; //if there is a Mu-AntiMu Conversion.
    G4UIcmdWithADouble* fMFPhysicsCmd;  //if there is a MuoniumFormation process.

//	G4UIcmdWithADoubleAndUnit*	fTSLengthCmd;

};

#endif
