//UICommand for ParticleSource.
#ifndef PGMessenger_h
#define PGMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PSIMACEPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADouble;

class PSIMACEPGAMessenger : public G4UImessenger {
private:
    PSIMACEPrimaryGeneratorAction* fPrimaryGeneratorAction;
    G4UIdirectory* fDirectory;
    G4UIcmdWithADouble* fPPECmd;

public:
    PSIMACEPGAMessenger(PSIMACEPrimaryGeneratorAction*);
    virtual ~PSIMACEPGAMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
};

#endif
